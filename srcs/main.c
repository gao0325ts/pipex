/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:42:25 by stakada           #+#    #+#             */
/*   Updated: 2024/12/19 17:38:56 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	t_data	*data;

	if (argc < 5)
	{
		ft_putendl_fd("Error: Invalid argument", STDERR_FILENO);
		return (1);
	}
	data = init_struct(argc, argv, envp);
	if (!data)
	{
		ft_putendl_fd("Error: Initialization failed", STDERR_FILENO);
		return (1);
	}
	if (data->is_here_doc == 1)
		run_here_doc_pipeline(data, &pid);
	else
		run_pipeline(data, &pid);
	free_data(data);
	return (get_last_exit_code(pid, data));
}
