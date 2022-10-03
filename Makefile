# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 22:56:41 by kle-guen          #+#    #+#              #
#    Updated: 2022/10/03 17:38:45 by chjoie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = Libft/libft.a
CC = @gcc -g
CFLAGS = -Wall -Wextra -Werror -I includes
LFLAGS = -L/usr/local/lib -I/usr/local/include -lreadline
SRCS = srcs/main.c \

OBJS = $(SRCS:.c=.o)

all : $(LIBFT) $(NAME)

$(LIBFT):
		@echo "\033[0;32m\033[0;33m Compiling Libft\033[0m"
		make	-sC Libft/
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

re: fclean all 

run: all 
	./$(NAME)
run2: all
	valgrind --suppressions=vsupp ./$(NAME)

.SILENT: 
.PHONY: re all clean fclean
