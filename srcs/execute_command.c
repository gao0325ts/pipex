/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 23:30:58 by stakada           #+#    #+#             */
/*   Updated: 2024/12/18 20:34:11 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_command_path(char *cmd_name, char **path_list)
{
	char	*path;
	char	*path_tail;
	int		i;

	i = 0;
	while (path_list[i])
	{
		path_tail = ft_strjoin("/", cmd_name);
		path = ft_strjoin(path_list[i], path_tail);
		free(path_tail);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

char	*check_command_path(char *cmd, char **path_list)
{
	if (ft_strncmp(cmd, "/", 1) == 0 || ft_strncmp(cmd, "./", 2) == 0
		|| ft_strncmp(cmd, "../", 3) == 0)
	{
		if (access(cmd, F_OK) == 0)
			return (ft_strdup(cmd));
		else
			return (NULL);
	}
	return (find_command_path(cmd, path_list));
}

void	execute_command(char **path_list, char *cmd_str, char **envp)
{
	char	*cmd_path;
	char	**cmd;

	cmd = ft_split(cmd_str, ' ');
	if (!cmd)
	{
		free_2d_array(path_list);
		exit(EXIT_FAILURE);
	}
	cmd_path = check_command_path(cmd[0], path_list);
	if (!cmd_path)
	{
		ft_dprintf(STDERR_FILENO, "%s: command not found\n", cmd[0]);
		free_2d_array(path_list);
		free_2d_array(cmd);
		exit(127);
	}
	if (execve(cmd_path, cmd, envp) == -1)
	{
		exit_with_message(1, cmd_path);
		free(cmd_path);
		free_2d_array(path_list);
		free_2d_array(cmd);
		exit(1);
	}
}
