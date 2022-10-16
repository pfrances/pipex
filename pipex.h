/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 15:20:46 by pfrances          #+#    #+#             */
/*   Updated: 2022/10/17 00:50:45 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <unistd.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# ifndef BONUS
#  define BONUS 0
# endif
# define BUFFER_SIZE 1024
# define MAIN_PROCESS 1
# define CHILD_PROCESS 0
# define FILE_DOES_NOT_EXIST_MSG ": No such file or directory\n"
# define COMMAND_NOT_FOUND ": command not found\n"
# define PERMISSION_DENIED ": Permission denied\n"
# define PATH_DOES_NOT_EXIST "/does_not_exist"
# define CMD_DOES_NOT_EXIST "does_not_exist"

typedef struct s_cmd
{
	char	*name;
	char	*path;
	char	**args;
}	t_cmd;

typedef struct s_utils
{
	char	*input;
	int		input_fd;
	bool	has_input;
	int		output_fd;
	int		**fd_array;
	int		*pids_array;
	char	**env_paths;
	bool	has_here_doc;
	size_t	nbr_of_cmds;
	t_cmd	**cmds;
}	t_utils;

/*		read_all.c			*/
char	*read_all(int fd);

/*		parsing.c			*/
bool	do_parsing(int argc, char *argv[], char *envp[], t_utils *utils);
/*		parsing_utils.c		*/
bool	set_path(t_cmd *cmd, char **env_paths);
bool	set_name_and_args(char *cmd_str, t_cmd *cmd);
bool	empty_cmd_process(char *cmd_str, t_cmd *cmd);
/*		here_doc_process.c	*/
bool	here_doc_process(char **args, t_utils *utils);

/*		pipex_utils.c		*/
void	closing_unused_fd(t_utils *utils, size_t index, int flag);
void	wait_all_process(size_t nbr_of_cmds);
bool	prepare_arrays(t_utils *utils);

/*		set_command_pipes.c	*/
void	set_pipes(t_utils *utils, size_t index);

/*		free_memory.c		*/
int		free_memory(t_utils *utils, int exit_code);
void	free_env_paths(char **env_paths);
void	free_cmds(t_utils *utils);

#endif