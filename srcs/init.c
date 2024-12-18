/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:59:38 by stakada           #+#    #+#             */
/*   Updated: 2024/12/18 20:36:40 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_here_doc(char *str)
{
	return (ft_strncmp(str, "here_doc", 8) == 0 && ft_strlen(str) == 8);
}

int	init_cmds(int cmd_count, char **argv, int offset, t_vars *vars)
{
	int	i;

	i = 0;
	vars->cmds = (char **)malloc(sizeof(char *) * (cmd_count + 1));
	if (!vars->cmds)
		return (-1);
	while (i < cmd_count)
	{
		vars->cmds[i] = argv[i + offset];
		i++;
	}
	vars->cmds[i] = NULL;
	return (0);
}

int	init_here_doc(int argc, char **argv, t_vars *vars)
{
	vars->is_here_doc = 1;
	vars->limiter = argv[2];
	vars->infile = TMP_FILE;
	vars->outfile = argv[argc - 1];
	vars->cmd_count = (argc - 1) - 3;
	return (init_cmds(vars->cmd_count, argv, 3, vars));
}

int	init_basic(int argc, char **argv, t_vars *vars)
{
	vars->is_here_doc = 0;
	vars->limiter = NULL;
	vars->infile = argv[1];
	vars->outfile = argv[argc - 1];
	vars->cmd_count = (argc - 1) - 2;
	return (init_cmds(vars->cmd_count, argv, 2, vars));
}

t_vars	*init_struct(int argc, char **argv, char **envp)
{
	t_vars	*vars;

	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		return (NULL);
	vars->path_list = get_path_list(envp);
	if (!vars->path_list)
	{
		free(vars);
		return (NULL);
	}
	if (is_here_doc(argv[1]) && init_here_doc(argc, argv, vars) == -1)
	{
		free_vars(vars);
		return (NULL);
	}
	else if (init_basic(argc, argv, vars) == -1)
	{
		free_vars(vars);
		return (NULL);
	}
	return (vars);
}
