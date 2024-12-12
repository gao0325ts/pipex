/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:59:38 by stakada           #+#    #+#             */
/*   Updated: 2024/12/12 14:05:45 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_vars	*init_pipex(int argc, char **argv)
{
	t_vars	*vars;

	vars = (t_vars *)malloc(sizeof(t_vars));
	if (!vars)
		return (NULL);
	if (is_here_doc(argv[1]))
	{
		if (init_here_doc(argc, argv, vars) == -1)
		{
			free(vars);
			return (NULL);
		}
	}
	else
	{
		if (init_basic(argc, argv, vars) == -1)
		{
			free(vars);
			return (NULL);
		}
	}
	return (vars);
}

int	is_here_doc(char *str)
{
	if (ft_strncmp(str, "here_doc", 8) == 0 && ft_strlen(str) == 8)
		return (1);
	return (0);
}

int	init_basic(int argc, char **argv, t_vars *vars)
{
	int	i;

	vars->is_here_doc = 0;
	vars->limiter = NULL;
	vars->infile = argv[1];
	vars->outfile = argv[argc - 1];
	vars->cmd_count = (argc - 1) - 2;
	vars->cmds = (char **)malloc(sizeof(char *) * (vars->cmd_count + 1));
	if (!vars->cmds)
		return (-1);
	i = 0;
	while (i < vars->cmd_count)
	{
		vars->cmds[i] = argv[2 + i];
        i++; 
	}
    vars->cmds[i] = NULL;
	return (0);
}

int	init_here_doc(int argc, char **argv, t_vars *vars)
{
	int	i;

	vars->is_here_doc = 1;
	vars->limiter = argv[2];
	vars->infile = NULL;
	vars->outfile = argv[argc - 1];
	vars->cmd_count = (argc - 1) - 3;
	vars->cmds = (char **)malloc(sizeof(char *) * (vars->cmd_count + 1));
	if (!vars->cmds)
		return (-1);
	i = 0;
	while (i < vars->cmd_count)
	{
        vars->cmds[i] = argv[i + 3];
		i++;
	}
    vars->cmds[i] = NULL;
	return (0);
}
