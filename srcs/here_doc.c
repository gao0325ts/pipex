/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:21:15 by stakada           #+#    #+#             */
/*   Updated: 2024/12/19 21:19:37 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_here_doc_streams(t_data *data)
{
	int	infile_fd;
	int	outfile_fd;

	infile_fd = open(data->infile, O_RDONLY);
	if (infile_fd < 0)
		exit_with_message(1, data->infile, data);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	outfile_fd = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile_fd < 0)
		exit_with_message(1, data->outfile, data);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
}

void	handle_here_doc_input(t_data *data)
{
	int		tmp_fd;
	char	*line;

	tmp_fd = open(data->infile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		exit_with_message(1, TMP_FILE, data);
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
	close(tmp_fd);
}

void	run_here_doc_pipeline(t_data *data, int *pid)
{
	handle_here_doc_input(data);
	(*pid) = fork();
	if (*pid < 0)
		exit_with_message(1, "fork", data);
	if (*pid == 0)
	{
		set_here_doc_streams(data);
		execute_command(data, data->cmds[0]);
	}
	unlink(TMP_FILE);
}
