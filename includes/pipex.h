/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:00:51 by stakada           #+#    #+#             */
/*   Updated: 2024/12/17 14:38:38 by stakada          ###   ########.fr       */
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

typedef struct s_vars
{
	int		is_here_doc;
	char	*limiter;
	char	*infile;
	char	*outfile;
	char	**cmds;
	int		cmd_count;
}			t_vars;

// get_path_list.c
char		**get_path_list(char **envp);
char		*find_path_str(char **envp);

// init.c
t_vars		*init_struct(int argc, char **argv);
int			is_here_doc(char *str);
int			init_basic(int argc, char **argv, t_vars *vars);
int			init_here_doc(int argc, char **argv, t_vars *vars);

// pipe.c
void		execute_pipeline(char **path_list, t_vars *vars, char **envp);
int			check_infile(char *infile);
int			check_outfile(char *outfile);
void		handle_error(char *str, int exit_status);

// execute_command.c
void		execute_command(char **path_list, char *cmd_str, char **envp);

// pipex.h
void		pipex(char **path_list, t_vars *vars, char **envp);
void		last_command(char **path_list, int iofd[2], t_vars *vars,
				char **envp);

// free.c
void		free_split(char **array);
void		free_vars(t_vars *vars);

#endif