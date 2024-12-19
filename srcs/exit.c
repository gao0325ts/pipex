/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:53:27 by stakada           #+#    #+#             */
/*   Updated: 2024/12/19 14:56:27 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_with_message(int exit_status, char *str, t_data *data)
{
	perror(str);
	free_data(data);
	exit(exit_status);
}

int	get_last_exit_code(pid_t pid, t_data *data)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		exit_with_message(1, "waitpid", data);
	return (WEXITSTATUS(status));
}
