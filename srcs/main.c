/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:00:38 by stakada           #+#    #+#             */
/*   Updated: 2024/12/18 05:02:30 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	pid_t	pid;
	t_vars	*vars;

	if (argc != 5)
	{
		ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 file2", STDERR_FILENO);
		return (1);
	}
	vars = init_struct(argc, argv);
	if (!vars)
		return (1);
	vars->path_list = get_path_list(envp);
	if (!vars->path_list)
	{
		free_vars(vars);
		return (1);
	}
	// if (vars->is_here_doc == 1)
	// 	execute_here_doc_pipeline(path_list, vars, envp);
	execute_pipeline(vars, envp, &pid);
	free_vars(vars);
	return (0);
}
