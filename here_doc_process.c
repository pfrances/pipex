/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:24:41 by pfrances          #+#    #+#             */
/*   Updated: 2022/09/23 16:30:51 by pfrances         ###   ########.fr       */
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
	utils->input = ft_calloc(1, sizeof(char));
	if (utils->input == NULL)
		return (false);
	while (1)
	{
		if (utils->nbr_of_cmds >= 2)
			write(STDOUT_FILENO, "pipe ", 5);
		write(STDOUT_FILENO, "here_doc> ", 10);
		line = get_next_line_until_limiter(STDIN_FILENO, limiter);
		if (line == NULL)
			break ;
		utils->input = ft_strjoin_with_free(utils->input, line);
		free(line);
	}
	free(limiter);
	return (true);
}
