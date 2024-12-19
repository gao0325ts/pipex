/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:15:51 by stakada           #+#    #+#             */
/*   Updated: 2024/12/19 22:09:42 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_input_stream(t_data *data, int pipefd[2])
{
	int	infile_fd;

	infile_fd = open(data->infile, O_RDONLY);
	if (infile_fd < 0)
		exit_with_message(1, data->infile, data);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
}

void	set_output_stream(t_data *data, int input_fd, int pipefd[2])
{
	int	outfile_fd;
	int	flag;

	if (data->is_here_doc)
		flag = O_APPEND;
	else
		flag = O_TRUNC;
	outfile_fd = open(data->outfile, O_WRONLY | O_CREAT | flag, 0644);
	if (outfile_fd < 0)
		exit_with_message(1, data->outfile, data);
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
	close(pipefd[1]);
	close(pipefd[0]);
}

void	set_pipe_stream(int input_fd, int pipefd[2])
{
	dup2(input_fd, STDIN_FILENO);
	close(input_fd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
}

void	set_streams(int i, t_data *data, int input_fd, int pipefd[2])
{
	if (i == 0)
		set_input_stream(data, pipefd);
	else if (i == data->cmd_count - 1)
		set_output_stream(data, input_fd, pipefd);
	else
		set_pipe_stream(input_fd, pipefd);
}

void	run_pipeline(t_data *data, pid_t *pid)
{
	int	pipefd[2];
	int	input_fd;
	int	i;

	i = 0;
	while (i < data->cmd_count)
	{
		if (pipe(pipefd) < 0)
			exit_with_message(1, "pipe", data);
		(*pid) = fork();
		if (*pid < 0)
			exit_with_message(1, "fork", data);
		if (*pid == 0)
		{
			set_streams(i, data, input_fd, pipefd);
			execute_command(data, data->cmds[i]);
		}
		close(pipefd[1]);
		input_fd = pipefd[0];
		i++;
	}
	close(input_fd);
}
