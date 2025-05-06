# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rd-agost <rd-agost@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/30 12:57:06 by cacorrea          #+#    #+#              #
#    Updated: 2025/04/26 18:47:03 by rd-agost         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror -g

SRCS = minishell.c list_utils.c utils.c tokenize.c environment.c ft_pwd.c \
		ft_env.c ft_export.c ft_unset.c singlequote.c ft_get_token.c \
		check_input.c parser.c parse_utils.c final_parse.c cmd_lst.c \
		executor.c ft_echo.c handle_redirection.c execute_cmdblocks.c \
		exec_utils.c
#da cambiare executer con exec per collegare al file di Roberta

LIBFT = ./libft/libft.a

all: $(NAME)

$(LIBFT):
	@make -C ./libft

$(NAME): $(SRCS) $(LIBFT)
	$(CC) $(SRCS) $(LIBFT) -o $(NAME) -lreadline
	@echo "\033[0;96mminishell compiled\033[0m"


val: all
		@mkdir -p ./supp
		@echo "{\n\tname=\"readline\"\n\tmalloc:reachable=1\n\tmatch-leak-kinds: reachable\n\t...\n}" > ./supp/supp.supp
		@echo "Created Valgrind suppression file"
		valgrind --leak-check=full --track-origins=yes -s --show-leak-kinds=all \
		--suppressions=./supp/supp.supp ./$(NAME)

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
