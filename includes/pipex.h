/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:00:51 by stakada           #+#    #+#             */
/*   Updated: 2024/12/18 20:35:50 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "get_next_line.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define TMP_FILE ".here_doc_tmp"

typedef struct s_vars
{
	int		is_here_doc;
	char	*limiter;
	char	*infile;
	char	*outfile;
	char	**cmds;
	char	**path_list;
	int		cmd_count;
}			t_vars;

// get_path_list.c
char		**get_path_list(char **envp);
char		*find_path_str(char **envp);

// init.c
t_vars		*init_struct(int argc, char **argv, char **envp);
int			is_here_doc(char *str);
int			init_basic(int argc, char **argv, t_vars *vars);
int			init_here_doc(int argc, char **argv, t_vars *vars);

// here_doc.c
void		run_here_doc_pipeline(t_vars *vars, char **envp, int *pid);
void		handle_here_doc_input(char *infile, char *limiter);
void		set_here_doc_streams(char *infile, char *outfile);

// pipeline.c
void		run_pipeline(t_vars *vars, char **envp, pid_t *pid);
void		set_streams(int i, t_vars *vars, int input_fd, int pipefd[2]);
void		set_input_stream(char *infile, int pipefd[2]);
void		set_output_stream(char *outfile, int input_fd, int pipefd[2]);
void		set_pipe_stream(int input_fd, int pipefd[2]);

// validate.c
int			validate_infile(char *infile);
int			validate_outfile(char *outfile);

// execute_command.c
void		execute_command(char **path_list, char *cmd_str, char **envp);
char		*check_command_path(char *cmd, char **path_list);
char		*find_command_path(char *cmd_name, char **path_list);

// free.c
void		free_2d_array(char **array);
void		free_vars(t_vars *vars);

// exit.c
void		exit_with_message(int exit_status, char *str);
int			get_last_exit_code(pid_t pid);

#endif