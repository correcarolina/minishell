# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/30 12:57:06 by cacorrea          #+#    #+#              #
#    Updated: 2025/04/26 17:17:48 by rd-agost         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = minishell.c list_utils.c utils.c tokenize.c environment.c ft_pwd.c \
		ft_env.c ft_export.c ft_unset.c singlequote.c ft_get_token.c \
		check_input.c parser.c parse_utils.c final_parse.c cmd_lst.c

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
val: all
        valgrind --leak-check=full --track-origins=yes -s --show-leak-kinds=all 
		--suppressions=./supp/supp.supp ./$(NAME)

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
