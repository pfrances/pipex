/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 23:22:29 by pfrances          #+#    #+#             */
/*   Updated: 2022/09/23 19:55:54 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	empty_cmd_process(char *cmd_str, t_cmd *cmd)
{
	if (cmd_str[0] != '\0')
		return (true);
	cmd->name = ft_strdup(CMD_DOES_NOT_EXIST);
	if (cmd->name == NULL)
		return (false);
	cmd->args = malloc(sizeof(char *) * 2);
	if (cmd->args == NULL)
	{
		free(cmd->name);
		return (false);
	}
	cmd->args[0] = ft_strdup(CMD_DOES_NOT_EXIST);
	if (cmd->args[0] == NULL)
	{
		free(cmd->args);
		free(cmd->name);
		return (false);
	}
	cmd->args[1] = NULL;
	return (true);
}

bool	set_name_and_args(char *cmd_str, t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (ft_is_space(cmd_str[i]))
		i++;
	while (1)
	{
		if (cmd_str[i] == '\0' || cmd_str[i] == ' ')
		{
			cmd->name = malloc(sizeof(char) * (i + 1));
			if (cmd->name == NULL)
				return (false);
			ft_strlcpy(cmd->name, cmd_str, i + 1);
			cmd->args = ft_split(cmd_str, ' ');
			if (cmd->args == NULL)
			{
				free(cmd->name);
				return (false);
			}
			break ;
		}
		i++;
	}
	return (true);
}

char	*join_to_create_full_path(char *path, char *name)
{
	char	*full_path;
	size_t	path_len;
	size_t	total_length;

	if (path == NULL || name == NULL)
		return (NULL);
	path_len = ft_strlen(path);
	total_length = path_len + ft_strlen(name) + 1;
	full_path = ft_calloc(total_length + 1, sizeof(char));
	if (full_path == NULL)
		return (NULL);
	ft_strlcpy(full_path, path, path_len + 1);
	full_path[path_len] = '/';
	ft_strlcat(full_path + path_len + 1, name, total_length + 1);
	return (full_path);
}

char	*search_cmds_path(char *name, char **env_paths, int *error_flag)
{
	char	*path;
	size_t	i;

	*error_flag = false;
	if (access(name, X_OK) == 0)
		return (ft_strdup(name));
	i = 0;
	while (env_paths[i] != NULL && name[0] != '\0')
	{
		path = join_to_create_full_path(env_paths[i], name);
		if (path == NULL)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_putstr_fd(name, STDERR_FILENO);
	ft_putstr_fd(COMMAND_NOT_FOUND, STDERR_FILENO);
	*error_flag = true;
	return (ft_strdup(PATH_DOES_NOT_EXIST));
}

bool	set_path(t_cmd *cmd, char **env_paths)
{
	int	error_flag;

	cmd->path = search_cmds_path(cmd->name, env_paths, &error_flag);
	if (cmd->path == NULL && error_flag == false)
		return (false);
	if (error_flag == false && access(cmd->path, X_OK) == -1)
	{
		ft_putstr_fd(BASH_MSG, STDERR_FILENO);
		ft_putstr_fd(cmd->path, STDERR_FILENO);
		ft_putstr_fd(PERMISSION_DENIED, STDERR_FILENO);
	}
	return (true);
}
