/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:42:25 by stakada           #+#    #+#             */
/*   Updated: 2024/12/20 09:30:42 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	pid_t	pid;
	t_data	*data;

	validate_argument(argc, argv);
	data = init_struct(argc, argv, envp);
	if (!data)
	{
		ft_putendl_fd("pipex: Initialization failed", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (data->is_here_doc)
	{
		handle_here_doc_input(data);
		run_here_doc_pipeline(data, &pid);
	}
	else
		run_pipeline(data, &pid);
	return (get_last_exit_code(pid, data));
}
