/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 22:25:52 by stakada           #+#    #+#             */
/*   Updated: 2024/12/10 22:49:22 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path_list(char **envp)
{
	char	*path_str;
	char	**path_list;

	path_str = find_path_str(envp);
	if (!path_str) // TODO エラーメッセージ出力？
		return (NULL);
	path_list = ft_split(path_str, ':');
	if (!path_list) // TODO エラーメッセージ出力？
		return (NULL);
	return (path_list);
}

char	*find_path_str(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (&envp[i][5]);
		i++;
	}
	return (NULL);
}