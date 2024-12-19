/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:53:27 by stakada           #+#    #+#             */
/*   Updated: 2024/12/19 22:07:43 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_with_message(int exit_status, char *str, t_data *data)
{
	ft_dprintf(STDERR_FILENO, "pipex: %s: %s\n", str, strerror(errno));
	free_data(data);
	exit(exit_status);
}

int	get_last_exit_code(pid_t pid, t_data *data)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		exit_with_message(1, "waitpid", data);
	if (data->is_here_doc)
		unlink(TMP_FILE);
	return (WEXITSTATUS(status));
}

void	validate_argument(int argc, char **argv)
{
	if (argc < 5)
	{
		ft_putendl_fd("pipex: Invalid argument", STDERR_FILENO);
		exit(1);
	}
	else if (is_here_doc(argv[1]) && argc < 6)
	{
		ft_putendl_fd("pipex: Invalid argument", STDERR_FILENO);
		exit(1);
	}
}