# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pfrances <pfrances@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/07 22:35:44 by pfrances          #+#    #+#              #
#    Updated: 2022/10/17 00:36:30 by pfrances         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
GNL_DIR = get_next_line
SRCS =	pipex.c							\
		pipex_utils.c					\
		read_all.c						\
		parsing.c						\
		parsing_utils.c					\
		here_doc_process.c				\
		free_memory.c					\
		set_command_pipes.c				\
		$(GNL_DIR)/get_next_line.c		\
		$(GNL_DIR)/get_next_line_utils.c
OBJS = $(SRCS:.c=.o)
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

ifdef WITH_BONUS
	CFLAGS += -D BONUS=1
endif

bonus:
	make all WITH_BONUS=TRUE

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR) bonus

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)

re: fclean all

.PHONY: all clean fclean re bonus