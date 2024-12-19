/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:21:15 by stakada           #+#    #+#             */
/*   Updated: 2024/12/19 22:21:28 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_here_doc_input(t_data *data)
{
	int		tmp_fd;
	char	*line;

	tmp_fd = open(data->infile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		exit_with_error(TMP_FILE, data);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strncmp(line, data->limiter,
				ft_strlen(data->limiter)) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		free(line);
	}
	close_safely(tmp_fd, data);
}

void	run_here_doc_pipeline(t_data *data, int *pid)
{
	int	pipefd[2];
	int	input_fd;
	int	i;

	handle_here_doc_input(data);
	i = 0;
	while (i < data->cmd_count)
	{
		if (pipe(pipefd) < 0)
			exit_with_error("pipe", data);
		(*pid) = fork();
		if (*pid < 0)
			exit_with_error("fork", data);
		if (*pid == 0)
		{
			set_streams(i, data, input_fd, pipefd);
			execute_command(data, data->cmds[i]);
		}
		close_safely(pipefd[1], data);
		input_fd = pipefd[0];
		i++;
	}
	close_safely(input_fd, data);
}
