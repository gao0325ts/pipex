/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 21:35:59 by stakada           #+#    #+#             */
/*   Updated: 2024/12/13 22:07:04 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_files_and_permissions(t_vars *vars)
{
	int errors;

	errors = 0;
	check_infile(vars->infile, &errors);
	check_outfile(vars->outfile, &errors);
	check_commands(vars->cmds, vars->cmd_count, &errors);
	return (errors);
}

void	check_infile(char *infile, int *errors)
{
	if (infile)
	{
		if (access(infile, F_OK) == -1)
			(*errors) |= IN_F_NG;
		else if (access(infile, R_OK) == -1)
			(*errors) |= IN_R_NG;
	}
}

void	check_outfile(char *outfile, int *errors)
{
	int fd;

	if (outfile)
	{
		if (access(outfile, F_OK) == -1)
		{
			fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				(*errors) |= OUT_C_NG;
			else
				close(fd);
		}
	}
	else if (access(outfile, W_OK) == -1)
		(*errors) |= OUT_W_NG;
}

void	check_commands(char **cmds, int cmd_count, int *errors)
{
	int i;

	i = 0;
	while (i < cmd_count)
	{
		if (access(cmds[i], F_OK) == -1 || access(cmds[i], X_OK) == -1)
			(*errors) |= CMD_NG;
		i++;
	}
}
