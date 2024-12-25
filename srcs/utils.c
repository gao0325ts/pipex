/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:53:27 by stakada           #+#    #+#             */
/*   Updated: 2024/12/25 14:48:38 by stakada          ###   ########.fr       */
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

void	exit_with_error(char *str, t_data *data, int exit_status)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", str, strerror(errno));
	free_data(data);
	exit(exit_status);
}

void	close_safely(int fd, t_data *data)
{
	if (close(fd) < 0)
		exit_with_error("close", data, 1);
}

void	dup2_safely(int oldfd, int newfd, t_data *data)
{
	if (dup2(oldfd, newfd) < 0)
		exit_with_error("dup2", data, 1);
}

int	get_last_exit_code(pid_t pid, t_data *data)
{
	int	status;

	if (waitpid(pid, &status, 0) < 0)
		exit_with_error("waitpid", data, 1);
	if (data->is_here_doc)
	{
		if (unlink(TMP_FILE) < 0)
			exit_with_error("unlink", data, 1);
	}
	free_data(data);
	return (WEXITSTATUS(status));
}
