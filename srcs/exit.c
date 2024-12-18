/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:53:27 by stakada           #+#    #+#             */
/*   Updated: 2024/12/18 20:36:31 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_with_message(int exit_status, char *str)
{
	ft_dprintf(STDERR_FILENO, "%s: %s\n", str, strerror(errno));
	exit(exit_status);
}

int	get_last_exit_code(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		exit_with_message(1, "waitpid");
	return (WEXITSTATUS(status));
}
