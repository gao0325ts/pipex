/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:15:51 by stakada           #+#    #+#             */
/*   Updated: 2024/12/18 05:02:06 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_error(char *str, int exit_status)
{
	ft_dprintf(STDERR_FILENO, "%s: %s\n", str, strerror(errno));
	exit(exit_status);
}

void	handle_input_fd(char *infile, int pipefd[2])
{
	int	infile_fd;

	if (check_infile(infile) == -1)
		handle_error(infile, 1);
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd < 0)
		handle_error(infile, 1);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
}

void	handle_output_fd(char *outfile, int input_fd, int pipefd[2])
{
	int outfile_fd;

	if (check_outfile(outfile) == -1)
		handle_error(outfile, 1);
	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
		handle_error(outfile, 1);
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close(pipefd[1]);
	close(pipefd[0]);
}

void	handle_middle_fd(int input_fd, int pipefd[2])
{
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
}

void	handle_fildes(int i, t_vars *vars, int input_fd, int pipefd[2])
{
	if (i == 0)
        handle_input_fd(vars->infile, pipefd);
    else if (i == vars->cmd_count - 1)
        handle_output_fd(vars->outfile, input_fd, pipefd);
    else
        handle_middle_fd(input_fd, pipefd);
}

void	execute_pipeline(t_vars *vars, char **envp, pid_t *pid)
{
	int	pipefd[2];
	int	input_fd;
	int i;

	input_fd = STDIN_FILENO;
	i = 0;
	while (i < vars->cmd_count)
	{
		if (pipe(pipefd) < 0)
			handle_error("pipe", 1);
		(*pid) = fork();
		if (*pid < 0)
			handle_error("fork", 1);
		if (*pid == 0)
		{
			handle_fildes(i, vars, input_fd, pipefd);
			execute_command(vars->path_list, vars->cmds[i], envp);
		}
		close(pipefd[1]);
		input_fd = pipefd[0];
		if (i == vars->cmd_count - 1)
			close(input_fd);
		i++;
	}
}
