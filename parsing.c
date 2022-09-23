/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:18:13 by pfrances          #+#    #+#             */
/*   Updated: 2022/09/23 19:37:41 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	parse_input_file(char **args, t_utils *utils)
{
	int	fd;

	if (utils->has_here_doc == true)
		return (here_doc_process(args, utils));
	if (access(args[1], F_OK) == -1)
	{
		ft_putstr_fd(BASH_MSG, STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(FILE_DOES_NOT_EXIST_MSG, STDERR_FILENO);
		return (false);
	}
	else if (access(args[1], R_OK) == -1)
	{
		ft_putstr_fd(BASH_MSG, STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd(PERMISSION_DENIED, STDERR_FILENO);
		return (false);
	}
	fd = open(args[1], O_RDONLY);
	if (fd == -1)
		return (false);
	utils->input = read_all(fd);
	close(fd);
	return (utils->input != NULL);
}

bool	parse_cmds(char **cmds, t_utils *utils)
{
	size_t	i;

	utils->cmds = malloc(sizeof(t_cmd *) * (utils->nbr_of_cmds + 1));
	if (utils->cmds == NULL)
		return (false);
	i = 0;
	while (i < utils->nbr_of_cmds)
	{
		utils->cmds[i] = malloc(sizeof(t_cmd));
		// if (cmds[i][0] == '\0'
		// 	&& empty_cmd_process(cmds[i], utils->cmds[i]) == false)
		// 	return (false);
		if (set_name_and_args(cmds[i], utils->cmds[i]) == false)
			return (false);
		if (set_path(utils->cmds[i], utils->env_paths) == false)
			return (false);
		i++;
	}
	utils->cmds[i] = NULL;
	return (true);
}

bool	parse_output(char *filename, t_utils *utils)
{
	if (utils->has_here_doc == false)
		utils->output_fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else
		utils->output_fd = open(filename, O_WRONLY | O_APPEND | O_CREAT, 0644);
	if (utils->output_fd == -1)
		return (false);
	return (true);
}

bool	parse_env_paths(char *envp[], t_utils *utils)
{
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			utils->env_paths = ft_split(&envp[i][5], ':');
			if (utils->env_paths == NULL)
				return (false);
			return (true);
		}
		i++;
	}
	free(utils->input);
	return (false);
}

bool	do_parsing(int argc, char *argv[], char *envp[], t_utils *utils)
{
	utils->has_here_doc = (ft_strncmp(argv[1], "here_doc", 9) == 0);
	if (argc < 4 + (utils->has_here_doc))
		return (false);
	if (parse_input_file(argv, utils) == false)
		return (false);
	if (parse_env_paths(envp, utils) == false)
		return (false);
	utils->nbr_of_cmds = argc - (3 + (utils->has_here_doc == true));
	if (parse_cmds(&argv[2 + (utils->has_here_doc == true)], utils) == false)
		return (false);
	if (parse_output(argv[argc - 1], utils) == false)
		return (false);
	return (true);
}
