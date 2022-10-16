/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_command_pipes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 00:32:40 by pfrances          #+#    #+#             */
/*   Updated: 2022/10/17 00:34:52 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	set_first_command_pipes(t_utils *utils)
{
	if (utils->has_here_doc == true)
	{
		dup2(utils->fd_array[0][0], STDIN_FILENO);
		close(utils->fd_array[0][0]);
	}
	else
	{
		dup2(utils->input_fd, STDIN_FILENO);
		close(utils->input_fd);
	}
	dup2(utils->fd_array[1][1], STDOUT_FILENO);
	close(utils->fd_array[1][1]);
}

void	set_last_command_pipes(t_utils *utils)
{
	dup2(utils->fd_array[utils->nbr_of_cmds - 1][0], STDIN_FILENO);
	dup2(utils->output_fd, STDOUT_FILENO);
	close(utils->fd_array[utils->nbr_of_cmds - 1][0]);
	close(utils->output_fd);
}

void	set_other_commands_pipes(t_utils *utils, size_t index)
{
	dup2(utils->fd_array[index][0], STDIN_FILENO);
	dup2(utils->fd_array[index + 1][1], STDOUT_FILENO);
	close(utils->fd_array[index][0]);
	close(utils->fd_array[index + 1][1]);
}

void	set_pipes(t_utils *utils, size_t index)
{
	closing_unused_fd(utils, index, CHILD_PROCESS);
	if (index == 0)
		set_first_command_pipes(utils);
	else if (index < utils->nbr_of_cmds - 1)
		set_other_commands_pipes(utils, index);
	else
		set_last_command_pipes(utils);
}
