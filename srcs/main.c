/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:00:38 by stakada           #+#    #+#             */
/*   Updated: 2024/12/10 23:34:51 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	pid_t pid;
	char	**path_list;
	char	**cmd;

	(void)argc;
	if (argc != 2)
		return (1);
	path_list = get_path_list(envp);
	cmd = ft_split(argv[1], ' ');
	pid = fork();
	if (pid == 0)
	{
		execute_command(path_list, cmd, envp);
	}
	free_split(cmd);
	free_split(path_list);
	return (0);
}
