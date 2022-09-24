/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:48:14 by pfrances          #+#    #+#             */
/*   Updated: 2022/09/22 17:55:07 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	execute_commands(t_utils *utils, char *envp[])
{
	size_t	i;

	i = 0;
	while (i < utils->nbr_of_cmds)
	{
		utils->pids_array[i] = fork();
		if (utils->pids_array[i] == -1)
			return (false);
		if (utils->pids_array[i] == 0)
		{
			closing_unused_fd(utils, i, CHILD_PROCESS);
			dup2(utils->fd_array[i][0], STDIN_FILENO);
			dup2(utils->fd_array[i + 1][1], STDOUT_FILENO);
			close(utils->fd_array[i][0]);
			close(utils->fd_array[i + 1][1]);
			if (execve(utils->cmds[i]->path, utils->cmds[i]->args, envp) == -1)
				return (false);
		}
		i++;
	}
	return (true);
}

bool	main_process_job(t_utils *utils)
{
	char	*str;

	closing_unused_fd(utils, utils->nbr_of_cmds, MAIN_PROCESS);
	write(utils->fd_array[0][1], utils->input, ft_strlen(utils->input));
	close(utils->fd_array[0][1]);
	wait_all_process(utils->nbr_of_cmds);
	str = read_all(utils->fd_array[utils->nbr_of_cmds][0]);
	if (str == NULL)
		return (false);
	close(utils->fd_array[utils->nbr_of_cmds][0]);
	if (write(utils->output_fd, str, ft_strlen(str)) == -1)
	{
		free(str);
		return (false);
	}
	free(str);
	return (true);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_utils	utils;

	if (argc < 4 || do_parsing(argc, argv, envp, &utils) == false)
		return (1);
	if (prepare_arrays(&utils) == false)
		return (free_memory(&utils, 2));
	if (execute_commands(&utils, envp) == false)
		return (free_memory(&utils, 3));
	if (main_process_job(&utils) == false)
		return (free_memory(&utils, 4));
	return (free_memory(&utils, 0));
}
