/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:52:51 by stakada           #+#    #+#             */
/*   Updated: 2024/12/12 14:22:22 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(char **path_list, t_vars *vars, char **envp)
{
	int		i;
	int		pipefd[2];
	int		iofd[2];
	pid_t	pid;

	iofd[0] = open(vars->infile, O_RDONLY);
	i = 2;
	while (i < vars->cmd_count)
	{
		pipe(pipefd);
		pid = fork();
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
	last_command(path_list, iofd, vars, envp);
	close(iofd[0]);
	close(iofd[1]);
}

void	last_command(char **path_list, int iofd[2], t_vars *vars, char **envp)
{
	pid_t pid;

	iofd[1] = open(vars->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
	{
		dup2(iofd[0], STDIN_FILENO);
		close(iofd[0]);
		dup2(iofd[1], STDOUT_FILENO);
		close(iofd[1]);
		execute_command(path_list, vars->cmds[vars->cmd_count - 1], envp);
	}
}
