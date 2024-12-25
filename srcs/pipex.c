/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:15:51 by stakada           #+#    #+#             */
/*   Updated: 2024/12/25 14:48:22 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_input_stream(t_data *data, int pipefd[2])
{
	int	infile_fd;

	infile_fd = open(data->infile, O_RDONLY);
	if (infile_fd < 0)
		exit_with_error(data->infile, data, 1);
	dup2_safely(infile_fd, STDIN_FILENO, data);
	close_safely(infile_fd, data);
	dup2_safely(pipefd[1], STDOUT_FILENO, data);
	close_safely(pipefd[1], data);
	close_safely(pipefd[0], data);
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
		exit_with_error(data->outfile, data, 1);
	dup2_safely(input_fd, STDIN_FILENO, data);
	close_safely(input_fd, data);
	dup2_safely(outfile_fd, STDOUT_FILENO, data);
	close_safely(outfile_fd, data);
	close_safely(pipefd[1], data);
	close_safely(pipefd[0], data);
}

void	set_pipe_stream(t_data *data, int input_fd, int pipefd[2])
{
	dup2_safely(input_fd, STDIN_FILENO, data);
	close_safely(input_fd, data);
	dup2_safely(pipefd[1], STDOUT_FILENO, data);
	close_safely(pipefd[1], data);
	close_safely(pipefd[0], data);
}

void	set_streams(int i, t_data *data, int input_fd, int pipefd[2])
{
	if (i == 0)
		set_input_stream(data, pipefd);
	else if (i == data->cmd_count - 1)
		set_output_stream(data, input_fd, pipefd);
	else
		set_pipe_stream(data, input_fd, pipefd);
}

void	run_pipeline(t_data *data, pid_t *pid)
{
	int	pipefd[2];
	int	input_fd;
	int	i;

	i = 0;
	input_fd = -1;
	while (i < data->cmd_count)
	{
		if (pipe(pipefd) < 0)
			exit_with_error("pipe", data, 1);
		(*pid) = fork();
		if (*pid < 0)
			exit_with_error("fork", data, 1);
		if (*pid == 0)
		{
			set_streams(i, data, input_fd, pipefd);
			execute_command(data, data->cmds[i]);
		}
		close_safely(pipefd[1], data);
		if (input_fd != -1)
			close_safely(input_fd, data);
		input_fd = pipefd[0];
		i++;
	}
	close_safely(input_fd, data);
}
