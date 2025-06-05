# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/30 12:57:06 by cacorrea          #+#    #+#              #
#    Updated: 2025/06/05 17:35:53 by rd-agost         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = minishell.c list_utils.c utils.c tokenize.c environment.c ft_pwd.c \
		ft_env.c ft_export.c ft_unset.c singlequote.c ft_get_token.c \
		check_input.c parser.c parse_utils.c redir_lst.c final_parse.c \
		cmd_lst.c executor.c handle_redirection.c execute_cmdblocks.c \
		exec_utils.c ft_echo.c ft_cd.c ft_exit.c heredoc.c signals.c \
		environment_utils.c ft_print_error.c heredoc_utils.c ft_init.c \
		builtins.c exec_utils2.c

LIBFT = ./libft/libft.a

all: $(NAME)

$(LIBFT):
	@make -C ./libft

$(NAME): $(SRCS) $(LIBFT)
	$(CC) $(CFLAGS) $(SRCS) $(LIBFT) -o $(NAME) -lreadline
	@echo "\033[0;96mminishell compiled\033[0m"


val: all
		@echo "\033[0;96mCreated Valgrind suppression file\033[0m"
		valgrind --leak-check=full --track-fds=yes --track-origins=yes -s --show-leak-kinds=all --suppressions=readline.supp ./$(NAME)
		

clean:
	@make clean -C ./libft
	rm -rf $(OBJS)
	@echo "\033[0;96mobject files cleaned\033[0m"

fclean:	clean
	@make fclean -C ./libft
	@rm -f $(NAME)
	@rm -rf ./supp
	@echo "\033[0;96mlibrary and executables has been deleted\033[0m"

re:	fclean all

.SILENT:

.PHONY: all clean fclean re
