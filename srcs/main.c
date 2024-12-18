/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:00:38 by stakada           #+#    #+#             */
/*   Updated: 2024/12/18 20:24:55 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	t_vars	*vars;

	if (argc < 5)
	{
		ft_putendl_fd("Usage: ./pipex file1 cmd1 cmd2 file2", STDERR_FILENO);
		return (1);
	}
	vars = init_struct(argc, argv, envp);
	if (!vars)
	{
		ft_putendl_fd("", STDERR_FILENO);
		return (1);
	}
	if (vars->is_here_doc == 1)
		run_here_doc_pipeline(vars, envp, &pid);
	else
		run_pipeline(vars, envp, &pid);
	free_vars(vars);
	return (get_last_exit_code(pid));
}
