/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:00:38 by stakada           #+#    #+#             */
/*   Updated: 2024/12/11 19:41:59 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	pid_t pid;
	char	**path_list;
	int	pipefd[2];
	int in_fd;
	int out_fd;

	if (argc != 5)
    {
        ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 file2", STDERR_FILENO);
		return (1);
    }
	path_list = get_path_list(envp);
	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		in_fd = open(argv[1], O_RDONLY);
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		execute_command(path_list, argv[2], envp);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
		close(pipefd[1]);
		out_fd = open(argv[4], O_RDWR | O_CREAT);
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
		execute_command(path_list, argv[3], envp);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	wait(NULL);
	wait(NULL);
	free_split(path_list);
	return (0);
}
