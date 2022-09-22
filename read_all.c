/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 17:39:17 by pfrances          #+#    #+#             */
/*   Updated: 2022/09/21 00:08:12 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static bool	do_allocation(char **str1, char **str2)
{
	*str1 = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (*str1 == NULL)
		return (false);
	*str2 = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (*str2 == NULL)
	{
		free(str1);
		return (false);
	}
	return (true);
}

static char	*free_and_return_null(char *str1, char *str2)
{
	free(str1);
	free(str2);
	return (NULL);
}

char	*read_all(int fd)
{
	char	*str1;
	char	*str2;
	ssize_t	read_count;
	size_t	total_count;

	if (do_allocation(&str1, &str2) == false)
		return (NULL);
	read_count = read(fd, str1, BUFFER_SIZE);
	total_count = read_count;
	if (read_count < 1)
		return (free_and_return_null(str1, str2));
	while (read_count == BUFFER_SIZE)
	{
		read_count = read(fd, str2, BUFFER_SIZE);
		total_count += read_count;
		if (read_count == -1)
			return (free_and_return_null(str1, str2));
		ft_strjoin(str1, str2);
	}
	free(str2);
	return (str1);
}
