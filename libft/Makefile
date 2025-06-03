# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cacorrea <cacorrea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/19 12:10:32 by cacorrea          #+#    #+#              #
#    Updated: 2025/06/03 16:07:34 by cacorrea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRC	:= ft_isalpha.c \
	ft_isdigit.c \
	ft_isalnum.c \
	ft_isascii.c \
	ft_isprint.c \
	ft_isspace.c \
	ft_strlen.c \
	ft_memset.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_toupper.c \
	ft_tolower.c \
	ft_chartostr.c \
	ft_strchr.c \
	ft_strrchr.c \
	ft_strncmp.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_strnstr.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_strdup.c \
	ft_substr.c \
	ft_strjoin.c \
	ft_strjoin_3.c \
	ft_strjoin_free_both.c \
	ft_strtrim.c \
	ft_split.c \
	ft_itoa.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_strcmp.c

OBJS	= $(SRC:%.c=%.o)	

CC	= gcc

FLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $@ $^
	@echo "\033[0;92mlibft.a ready\033[0;39m"

%.o:%.c
	@$(CC) -c $(FLAGS) -I. $< -o $@

clean:
	rm -f $(OBJS)
	@echo "\033[0;92mcleaned object files\033[0;39m"

fclean: clean
	rm -f $(NAME)
	@echo "\033[0;92mlibft cleaned\033[0;39m"

re: fclean all

.PHONY : all clean fclean re
