# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacorrea <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/30 12:57:06 by cacorrea          #+#    #+#              #
#    Updated: 2025/01/30 12:57:11 by cacorrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = minishell.c list_utils.c utils.c tokenize.c environment.c ft_pwd.c \
		ft_env.c ft_export.c ft_unset.c singlequote.c ft_get_token.c \
		check_input.c parser.c parse_utils.c

OBJS = $(SRCS:%.c=%.o)

LIBFT = ./libft/libft.a

all: $(NAME)

$(LIBFT):
	@make -C ./libft

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "\033[0;96mminishell compiled\033[0m"

%.o: %.c
	@$(CC) -c $(CFLAGS) -I. $< -o $@

clean:
	@make clean -C ./libft
	rm -rf $(OBJS)
	@echo "\033[0;96mobject files cleaned\033[0m"

fclean:	clean
	@make fclean -C ./libft
	rm -f $(NAME)
	@echo "\033[0;96mlibrary and executables has been deleted\033[0m"

re:	fclean all

.SILENT:

.PHONY: all clean fclean re
