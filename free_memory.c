/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 23:31:50 by pfrances          #+#    #+#             */
/*   Updated: 2022/09/22 17:16:41 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_fd_array(t_utils *utils)
{
	size_t	i;

	i = 0;
	while (i < utils->nbr_of_cmds + 1)
	{
		free(utils->fd_array[i]);
		i++;
	}
	free(utils->fd_array);
}

void	free_cmds(t_utils *utils)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < utils->nbr_of_cmds)
	{
		j = 0;
		while (utils->cmds[i]->args[j] != NULL)
		{
			free(utils->cmds[i]->args[j]);
			j++;
		}
		free(utils->cmds[i]->args);
		free(utils->cmds[i]->name);
		free(utils->cmds[i]->path);
		free(utils->cmds[i]);
		i++;
	}
	free(utils->cmds);
}

void	free_env_paths(char **env_paths)
{
	size_t	i;

	i = 0;
	while (env_paths[i] != NULL)
	{
		free(env_paths[i]);
		i++;
	}
	free(env_paths);
}

int	free_memory(t_utils *utils, int exit_code)
{
	free(utils->pids_array);
	free(utils->input);
	free_fd_array(utils);
	if (utils->nbr_of_cmds > 0)
	{
		free_env_paths(utils->env_paths);
		free_cmds(utils);
	}
	return (exit_code);
}
