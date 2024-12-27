/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 12:00:51 by stakada           #+#    #+#             */
/*   Updated: 2024/12/27 02:49:09 by stakada          ###   ########.fr       */
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

# define TMP_FILE "/tmp/.here_doc_tmp"

typedef struct s_data
{
	int		is_here_doc;
	char	*limiter;
	char	*infile;
	char	*outfile;
	char	**cmds;
	int		cmd_count;
	char	**path_list;
	char	**envp;
}			t_data;

int			set_path_list(t_data *data, char **envp);
char		*find_path_str(char **envp);
t_data		*init_struct(int argc, char **argv, char **envp);
int			is_here_doc(char *str);
int			init_basic(int argc, char **argv, t_data *data);
int			init_here_doc(int argc, char **argv, t_data *data);
void		run_here_doc_pipeline(t_data *data, int *pid);
void		handle_here_doc_input(t_data *data);
void		run_pipeline(t_data *data, pid_t *pid);
void		set_streams(int i, t_data *data, int input_fd, int pipefd[2]);
void		set_input_stream(t_data *data, int pipefd[2]);
void		set_output_stream(t_data *data, int input_fd, int pipefd[2]);
void		set_pipe_stream(t_data *data, int input_fd, int pipefd[2]);
void		execute_command(t_data *data, char *cmd_str);
char		*check_command_path(char *cmd, t_data *data);
char		*find_command_path(char *cmd_name, char **path_list);
void		free_2d_array(char **array);
void		free_data(t_data *data);
void		exit_with_error(char *str, t_data *data, int exit_status);
void		close_safely(int fd, t_data *data);
void		dup2_safely(int oldfd, int newfd, t_data *data);
int			get_last_exit_code(t_data *data);
void		validate_argument(int argc, char **argv);

#endif