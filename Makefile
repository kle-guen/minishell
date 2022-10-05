# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 22:56:41 by kle-guen          #+#    #+#              #
#    Updated: 2022/10/05 18:00:25 by kle-guen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = Libft/libft.a
CC = @gcc
CFLAGS = -Wall -Wextra -Werror -I includes
LFLAGS = -L/usr/local/lib -I/usr/local/include -lreadline
SRCS = srcs/main.c \
	   srcs/parsing.c \
	   srcs/built_ins.c \
	   srcs/path_function.c \
	   srcs/utils.c \

OBJS = $(SRCS:.c=.o)

all : $(LIBFT) $(NAME)

$(LIBFT):
	@echo "\033[0;32m\033[0;33m Compiling Libft\033[0m"
	make -sC Libft/
	@echo "\033[0;32m\033[0;32m Done\033[0m"

$(NAME): $(OBJS) $(LIBFT)
	@echo "\033[0;32m\033[0;33m Compiling Minishell\033[0m"
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LFLAGS) -o $(NAME) 
	@echo "\033[0;32m\033[0;32m Done\033[0m"
	@tput blink; echo " 🎉🎉🎉🎉"; tput sgr0

clean:
	@echo "\033[0;32m\033[0;33m Cleaning..\033[0m"
	@rm -rf $(OBJS)
	@make -sC Libft/ clean
	@echo "\033[0;32m\033[0;32m Done\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@make -sC Libft/ fclean

re: fclean all 

.SILENT: 
.PHONY: re all clean fclean
