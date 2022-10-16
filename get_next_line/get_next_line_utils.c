/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:32:29 by pfrances          #+#    #+#             */
/*   Updated: 2022/10/17 01:19:15 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*dup;
	size_t	size;

	size = ft_strlen(s) + 1;
	if (size > n)
		size = n + 1;
	dup = malloc(sizeof(char) * (size));
	if (dup != NULL)
		ft_strlcpy(dup, s, size);
	return (dup);
}

char	*ft_strjoin_with_free(char *s1, char const *s2)
{
	char	*result;
	size_t	s1_len;
	size_t	s2_len;
	size_t	total_length;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	total_length = s1_len + s2_len;
	result = malloc(sizeof(char) * (total_length + 1));
	if (result == NULL)
		return (result);
	ft_strlcpy(result, s1, s1_len + 1);
	ft_strlcpy(result + s1_len, s2, s2_len + 1);
	free(s1);
	return (result);
}
