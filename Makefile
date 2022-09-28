# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 22:56:41 by kle-guen          #+#    #+#              #
#    Updated: 2022/09/27 22:45:54 by kle-guen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = @gcc
CFLAGS = -Wall -Wextra -Werror -I includes
LFLAGS = -L/usr/local/lib -I/usr/local/include -lreadline
SRCS = srcs/main.c \

OBJS = $(SRCS:.c=.o)

all :  $(NAME)

$(NAME): $(OBJS)
	@echo "\033[0;32m\033[0;33m Compiling Minishell\033[0m"
	$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) -o $(NAME) 
	@echo "\033[0;32m\033[0;32m Done\033[0m"
	@tput blink; echo " 🎉🎉🎉🎉"; tput sgr0


clean:
	@echo "\033[0;32m\033[0;33m Cleaning..\033[0m"
	@rm -rf $(OBJS)
	@echo "\033[0;32m\033[0;32m Done\033[0m"

fclean: clean
	@rm -rf $(NAME)

re: fclean all 

run: all 
	./$(NAME)

.SILENT: 
.PHONY: re all clean fclean
