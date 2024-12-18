/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 15:21:15 by stakada           #+#    #+#             */
/*   Updated: 2024/12/18 20:35:07 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_here_doc_streams(char *infile, char *outfile)
{
	int	infile_fd;
	int	outfile_fd;

	if (validate_infile(infile) == -1)
		exit_with_message(1, infile);
	if (validate_outfile(outfile) == -1)
		exit_with_message(1, outfile);
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd < 0)
		exit_with_message(1, infile);
	dup2(infile_fd, STDIN_FILENO);
	close(infile_fd);
	outfile_fd = open(outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile_fd < 0)
		exit_with_message(1, outfile);
	dup2(outfile_fd, STDOUT_FILENO);
	close(outfile_fd);
}

void	handle_here_doc_input(char *infile, char *limiter)
{
	int		tmp_fd;
	char	*line;

	tmp_fd = open(infile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		exit_with_message(1, TMP_FILE);
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line || ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		write(tmp_fd, line, ft_strlen(line));
		free(line);
	}
	close(tmp_fd);
}

void	run_here_doc_pipeline(t_vars *vars, char **envp, int *pid)
{
	handle_here_doc_input(vars->infile, vars->limiter);
	(*pid) = fork();
	if (*pid < 0)
		exit_with_message(1, "fork");
	if (*pid == 0)
	{
		set_here_doc_streams(vars->infile, vars->outfile);
		execute_command(vars->path_list, vars->cmds[0], envp);
	}
	wait(NULL);
	unlink(TMP_FILE);
}
