/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 18:15:51 by stakada           #+#    #+#             */
/*   Updated: 2024/12/18 20:35:36 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_input_stream(char *infile, int pipefd[2])
{
	int	infile_fd;

	if (validate_infile(infile) == -1)
		exit_with_message(1, infile);
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd < 0)
		exit_with_message(1, infile);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
}

void	set_output_stream(char *outfile, int input_fd, int pipefd[2])
{
	int	outfile_fd;

	if (validate_outfile(outfile) == -1)
		exit_with_message(1, outfile);
	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile_fd < 0)
		exit_with_message(1, outfile);
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

void	set_streams(int i, t_vars *vars, int input_fd, int pipefd[2])
{
	if (i == 0)
		set_input_stream(vars->infile, pipefd);
	else if (i == vars->cmd_count - 1)
		set_output_stream(vars->outfile, input_fd, pipefd);
	else
		set_pipe_stream(input_fd, pipefd);
}

void	run_pipeline(t_vars *vars, char **envp, pid_t *pid)
{
	int	pipefd[2];
	int	input_fd;
	int	i;

	input_fd = STDIN_FILENO;
	i = 0;
	while (i < vars->cmd_count)
	{
		if (pipe(pipefd) < 0)
			exit_with_message(1, "pipe");
		(*pid) = fork();
		if (*pid < 0)
			exit_with_message(1, "fork");
		if (*pid == 0)
		{
			set_streams(i, vars, input_fd, pipefd);
			execute_command(vars->path_list, vars->cmds[i], envp);
		}
		close(pipefd[1]);
		input_fd = pipefd[0];
		i++;
	}
	close(input_fd);
}
