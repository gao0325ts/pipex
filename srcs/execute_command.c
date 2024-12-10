/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 23:30:58 by stakada           #+#    #+#             */
/*   Updated: 2024/12/10 23:44:51 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute_command(char **path_list, char **cmd, char **envp)
{
	char *path;
	char *path_tail;
	int i;

	i = 0;
	while (path_list[i])
	{
		path_tail = ft_strjoin("/", cmd[0]);
		path = ft_strjoin(path_list[i], path_tail);
		free(path_tail);
		if (execve(path, cmd, envp) == -1)
		{
			free(path);
			i++;
		}
	}
	free_split(path_list);
	free_split(cmd);
	ft_putendl_fd("Error: command not found", STDERR_FILENO);
	exit(1);
}
