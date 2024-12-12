/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:52:51 by stakada           #+#    #+#             */
/*   Updated: 2024/12/12 13:28:28 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipex(char **path_list, int argc, char **argv, char **envp)
{
	int		i;
	int		pipefd[2];
	int		iofd[2];
	pid_t	pid;

	iofd[0] = open(argv[1], O_RDONLY);
	i = 2;
	while (i < argc - 2)
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
			execute_command(path_list, argv[i], envp);
		}
		close(pipefd[1]);
		close(iofd[0]);
		iofd[0] = pipefd[0];
		i++;
	}
	last_command(path_list, iofd, argv[argc - 1], argv[argc - 2], envp);
	close(iofd[0]);
	close(iofd[1]);
}

void	last_command(char **path_list, int iofd[2], char *outfile,
		char *last_cmd, char **envp)
{
	pid_t pid;

	iofd[1] = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	pid = fork();
	if (pid == 0)
	{
		dup2(iofd[0], STDIN_FILENO);
		close(iofd[0]);
		dup2(iofd[1], STDOUT_FILENO);
		close(iofd[1]);
		execute_command(path_list, last_cmd, envp);
	}
}
