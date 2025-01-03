/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:53:27 by stakada           #+#    #+#             */
/*   Updated: 2025/01/01 23:40:49 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	validate_argument(int argc, char **argv)
{
	if (argc < 5)
	{
		ft_putendl_fd("pipex: Invalid argument", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else if (is_here_doc(argv[1]) && argc < 6)
	{
		ft_putendl_fd("pipex: Invalid argument", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
}

void	exit_with_error(char *str, t_data *data)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", str, strerror(errno));
	free_data(data);
	exit(EXIT_FAILURE);
}

void	close_safely(int fd, t_data *data)
{
	if (close(fd) < 0)
		exit_with_error("close", data);
}

void	dup2_safely(int oldfd, int newfd, t_data *data)
{
	if (dup2(oldfd, newfd) < 0)
		exit_with_error("dup2", data);
}

int	get_last_exit_code(t_data *data)
{
	int	i;
	int	status;
	int	exit_code;

	exit_code = EXIT_SUCCESS;
	i = 0;
	while (i < data->cmd_count)
	{
		if (wait(&status) < 0)
			exit_with_error("wait", data);
		if ((WIFEXITED(status) && WEXITSTATUS(status) != 0)
			|| (WIFSIGNALED(status)))
			exit_code = EXIT_FAILURE;
		i++;
	}
	if (data->here_doc_flag)
	{
		if (unlink(TMP_FILE) < 0)
			exit_with_error("unlink", data);
	}
	free_data(data);
	return (exit_code);
}
