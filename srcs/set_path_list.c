/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_path_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:25:52 by stakada           #+#    #+#             */
/*   Updated: 2024/12/20 04:30:32 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path_str(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
}

int	set_path_list(t_data *data, char **envp)
{
	char	*path_str;

	path_str = find_path_str(envp);
	if (!path_str)
	{
		data->path_list = NULL;
		return (0);
	}
	data->path_list = ft_split(path_str, ':');
	if (!data->path_list)
		return (-1);
	return (0);
}
