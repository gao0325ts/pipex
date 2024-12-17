/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:15:51 by stakada           #+#    #+#             */
/*   Updated: 2024/12/17 15:09:29 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_pipeline(char **path_list, t_vars *vars, char **envp)
{
	int		pipefd[2];
	int		iofd[2] = {-1, -1};
	int		i;
	pid_t	pid;

	pipe(pipefd);
	pid = fork();
	if (pid < 0)
		handle_error("fork", 1);
	if (pid == 0)
	{
		if (check_infile(vars->infile) == -1)
			handle_error(vars->infile, 1);
		iofd[0] = open(vars->infile, O_RDONLY);
		if (iofd[0] < 0)
			handle_error(vars->infile, 1);
		dup2(iofd[0], STDIN_FILENO);
		close(iofd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		execute_command(path_list, vars->cmds[0], envp);
	}
	close(pipefd[1]);
	iofd[0] = pipefd[0];
	i = 1;
	while (i < vars->cmd_count - 1)
	{
		pipe(pipefd);
		pid = fork();
		if (pid < 0)
			handle_error("fork", 1);
		if (pid == 0)
		{
			dup2(iofd[0], STDIN_FILENO);
			close(iofd[0]);
			dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[1]);
			close(pipefd[0]);
			execute_command(path_list, vars->cmds[i], envp);
		}
		close(pipefd[1]);
		close(iofd[0]);
		iofd[0] = pipefd[0];
		i++;
	}
	pid = fork();
	if (pid < 0)
		handle_error("fork", 1);
	if (pid == 0)
	{
		if (check_outfile(vars->outfile) == -1)
			handle_error(vars->outfile, 1);
		iofd[1] = open(vars->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (iofd[1] < 0)
			handle_error(vars->outfile, 1);
		dup2(iofd[0], STDIN_FILENO);
		close(iofd[0]);
		dup2(iofd[1], STDOUT_FILENO);
		close(iofd[1]);
		execute_command(path_list, vars->cmds[i], envp);
	}
	close(iofd[0]);
	close(iofd[1]);
}

int	check_infile(char *infile)
{
	if (access(infile, F_OK) == -1)
	{
		return (-1);
	}
	else if (access(infile, R_OK) == -1)
	{
		return (-1);
	}
	return (0);
}

int	check_outfile(char *outfile)
{
	int	fd;

	if (access(outfile, F_OK) == -1)
		return (0);
	fd = open(outfile, O_WRONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}

void	handle_error(char *str, int exit_status)
{
	perror(str);
	exit(exit_status);
}
