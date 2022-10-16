/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 23:18:26 by pfrances          #+#    #+#             */
/*   Updated: 2022/10/17 00:31:10 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	prepare_arrays(t_utils *utils)
{
	size_t	i;

	utils->fd_array = malloc(sizeof(int *) * (utils->nbr_of_cmds + 1));
	if (utils->fd_array == NULL)
		return (false);
	i = 0;
	while (i < utils->nbr_of_cmds + 1)
	{
		utils->fd_array[i] = malloc(sizeof(int) * 2);
		if (utils->fd_array[i] == NULL)
			return (false);
		if (pipe(utils->fd_array[i]) == -1)
			return (false);
		i++;
	}
	utils->pids_array = malloc(sizeof(int) * utils->nbr_of_cmds);
	if (utils->pids_array == NULL)
		return (false);
	return (true);
}

void	wait_all_process(size_t nbr_of_cmds)
{
	size_t	i;

	i = 0;
	while (i < nbr_of_cmds)
	{
		wait(NULL);
		i++;
	}
}

void	closing_unused_fd(t_utils *utils, size_t index, int flag)
{
	size_t	i;

	i = 0;
	while (i < utils->nbr_of_cmds + 1)
	{
		if (flag == CHILD_PROCESS && index != i)
			close(utils->fd_array[i][0]);
		if (flag == CHILD_PROCESS && index + 1 != i)
			close(utils->fd_array[i][1]);
		if (flag == MAIN_PROCESS && utils->nbr_of_cmds != i)
			close(utils->fd_array[i][0]);
		if (flag == MAIN_PROCESS && i != 0)
			close(utils->fd_array[i][1]);
		i++;
	}
}
