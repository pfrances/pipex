/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:26:15 by pfrances          #+#    #+#             */
/*   Updated: 2022/09/22 17:00:48 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_and_return(char *result, char **save, char *buff, int flag)
{
	free(buff);
	if (flag == SUCCESS)
		return (result);
	free(result);
	free(*save);
	*save = NULL;
	return (NULL);
}

static int	initialisation(char **result, char **save, char **buff)
{
	if (*save)
	{
		*result = *save;
		*save = NULL;
	}
	else
	{
		*result = ft_strndup("", 1);
		if (!*result)
			return (ERROR);
	}
	*buff = malloc(sizeof(char) * ((size_t)GNL_BUFFER_SIZE + 1));
	if (!*buff)
		return (ERROR);
	return (SUCCESS);
}

static int	search_line_break(char **result, char **save, size_t *i)
{
	while ((*result)[*i] != '\0')
	{
		if ((*result)[*i] == '\n')
		{
			*save = ft_strndup(*result + *i + 1, ft_strlen(*result + *i + 1));
			if (!*save)
				return (ERROR);
			ft_bzero(&(*result)[*i + 1], ft_strlen(&(*result)[*i + 1]));
			return (SUCCESS);
		}
		(*i)++;
	}
	return (CONTINUE);
}

static char	*get_line_and_save(char **result, char **save, char **buff, int fd)
{
	int		line_break_flag;
	size_t	i;
	ssize_t	nb_read;

	i = 0;
	while (1)
	{
		ft_bzero(*buff, ((size_t)GNL_BUFFER_SIZE + 1));
		nb_read = read(fd, *buff, GNL_BUFFER_SIZE);
		if (nb_read <= 0 && (!**result || !(*result)[i]))
			return (free_and_return(*result, save, *buff, **result != '\0'));
		*result = ft_strjoin_with_free(*result, *buff);
		if (!*result)
			return (free_and_return(*result, save, *buff, ERROR));
		line_break_flag = search_line_break(result, save, &i);
		if (line_break_flag == SUCCESS || line_break_flag == ERROR)
			return (free_and_return(*result, save, *buff, line_break_flag));
	}
}

char	*get_next_line_until_limiter(int fd, char *limiter)
{
	static char	*save[10240] = {NULL};
	char		*buff;
	char		*result;

	if (fd < 0 || fd >= 10240 || GNL_BUFFER_SIZE <= 0)
		return (NULL);
	if (initialisation(&result, &save[fd], &buff) == ERROR)
		return (NULL);
	result = get_line_and_save(&result, &save[fd], &buff, fd);
	if (ft_strncmp(result, limiter, ft_strlen(limiter)) == 0)
	{
		free(save[fd]);
		free(result);
		return (NULL);
	}
	else
		return (result);
}
