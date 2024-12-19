/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:59:38 by stakada           #+#    #+#             */
/*   Updated: 2024/12/19 17:39:49 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_here_doc(char *str)
{
	return (ft_strncmp(str, "here_doc", 8) == 0 && ft_strlen(str) == 8);
}

int	init_cmds(int cmd_count, char **argv, int offset, t_data *data)
{
	int	i;

	i = 0;
	data->cmds = (char **)malloc(sizeof(char *) * (cmd_count + 1));
	if (!data->cmds)
		return (-1);
	while (i < cmd_count)
	{
		data->cmds[i] = argv[i + offset];
		i++;
	}
	data->cmds[i] = NULL;
	return (0);
}

int	init_here_doc(int argc, char **argv, t_data *data)
{
	data->is_here_doc = 1;
	data->limiter = argv[2];
	data->infile = TMP_FILE;
	data->outfile = argv[argc - 1];
	data->cmd_count = (argc - 1) - 3;
	return (init_cmds(data->cmd_count, argv, 3, data));
}

int	init_basic(int argc, char **argv, t_data *data)
{
	data->is_here_doc = 0;
	data->limiter = NULL;
	data->infile = argv[1];
	data->outfile = argv[argc - 1];
	data->cmd_count = (argc - 1) - 2;
	return (init_cmds(data->cmd_count, argv, 2, data));
}

t_data	*init_struct(int argc, char **argv, char **envp)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->path_list = get_path_list(envp);
	if (!data->path_list)
	{
		free(data);
		return (NULL);
	}
	data->envp = envp;
	if (is_here_doc(argv[1]) && init_here_doc(argc, argv, data) == -1)
	{
		free_data(data);
		return (NULL);
	}
	else if (init_basic(argc, argv, data) == -1)
	{
		free_data(data);
		return (NULL);
	}
	return (data);
}
