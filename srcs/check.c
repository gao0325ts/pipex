/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 04:00:18 by stakada           #+#    #+#             */
/*   Updated: 2024/12/18 04:29:43 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_infile(char *infile)
{
	if (access(infile, F_OK) == -1)
		return (-1);
	else if (access(infile, R_OK) == -1)
		return (-1);
	return (0);
}

int	check_outfile(char *outfile)
{
	int	fd;

	if (access(outfile, F_OK) == -1)
		return (0);
	fd = open(outfile, O_WRONLY);
	if (fd < 0)
		return (-1);
	close(fd);
	return (0);
}
