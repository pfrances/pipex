/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 15:21:04 by pfrances          #+#    #+#             */
/*   Updated: 2022/09/30 16:01:25 by pfrances         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define GNL_BUFFER_SIZE 1024
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

typedef enum e_bool
{
	FALSE,
	TRUE
}		t_bool;

typedef enum e_success
{
	ERROR,
	SUCCESS,
	CONTINUE
}		t_success;

char	*get_next_line_until_limiter(int fd, char *limiter);
char	*ft_strjoin_with_free(char *s1, char const *s2);
char	*ft_strndup(const char *s, size_t n);

#endif