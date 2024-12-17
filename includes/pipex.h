/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:00:51 by stakada           #+#    #+#             */
/*   Updated: 2024/12/17 22:55:01 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>

typedef struct s_vars
{
	int		is_here_doc;
	char	*limiter;
	char	*infile;
	char	*outfile;
	char	**cmds;
	int		cmd_count;
}			t_vars;

char		**get_path_list(char **envp);
char		*find_path_str(char **envp);
t_vars		*init_struct(int argc, char **argv);
int			is_here_doc(char *str);
int			init_basic(int argc, char **argv, t_vars *vars);
int			init_here_doc(int argc, char **argv, t_vars *vars);
void		execute_pipeline(char **path_list, t_vars *vars, char **envp);
void		handle_error(char *str, int exit_status);
void		execute_command(char **path_list, char *cmd_str, char **envp);
void		free_split(char **array);
// void		free_vars(t_vars *vars);

#endif