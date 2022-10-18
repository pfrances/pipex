/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 15:48:14 by pfrances          #+#    #+#             */
/*   Updated: 2022/10/18 12:09:36 by pfrances         ###   ########.fr       */
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
			set_pipes(utils, i);
			if (execve(utils->cmds[i]->path, utils->cmds[i]->args, envp) == -1)
				exit(EXIT_FAILURE);
		}
		i++;
	}
	closing_unused_fd(utils, utils->nbr_of_cmds, MAIN_PROCESS);
	if (utils->has_here_doc == true || utils->has_input == false)
	{
		write(utils->fd_array[0][1], utils->input, ft_strlen(utils->input));
		close(utils->fd_array[0][1]);
	}
	wait_all_process(utils->nbr_of_cmds);
	return (true);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_utils	utils;

	if (argc < 5 || do_parsing(argc, argv, envp, &utils) == false)
		return (1);
	if (prepare_arrays(&utils) == false)
		return (free_memory(&utils, 2));
	if (execute_commands(&utils, envp) == false)
		return (free_memory(&utils, 3));
	return (free_memory(&utils, 0));
}
