/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:24:41 by pfrances          #+#    #+#             */
/*   Updated: 2022/10/17 00:32:17 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

bool	here_doc_process(char **args, t_utils *utils)
{
	char	*limiter;
	char	*line;

	limiter = ft_strjoin_with_free(ft_strdup(args[2]), "\n");
	if (limiter == NULL)
		return (false);
	utils->hd_str = ft_calloc(1, sizeof(char));
	if (utils->hd_str == NULL)
		return (false);
	while (1)
	{
		if (utils->nbr_of_cmds >= 2)
			write(STDOUT_FILENO, "pipe ", 5);
		write(STDOUT_FILENO, "here_doc> ", 10);
		line = get_next_line_until_limiter(STDIN_FILENO, limiter);
		if (line == NULL)
			break ;
		utils->hd_str = ft_strjoin_with_free(utils->hd_str, line);
		free(line);
	}
	free(limiter);
	return (true);
}
