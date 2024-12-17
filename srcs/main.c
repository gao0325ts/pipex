/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:00:38 by stakada           #+#    #+#             */
/*   Updated: 2024/12/17 14:38:59 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	char	**path_list;
	t_vars	*vars;

	if (argc < 5)
	{
		ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 file2", STDERR_FILENO);
		return (1);
	}
	path_list = get_path_list(envp);
	if (!path_list)
		return (1);
	vars = init_struct(argc, argv);
	if (!vars)
	{
		free_split(path_list);
		return (1);
	}
	execute_pipeline(path_list, vars, envp);
	while (wait(NULL) > 0)
		;
	free_split(path_list);
	free(vars->cmds);
	free(vars);
	return (0);
}
