# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 22:56:41 by kle-guen          #+#    #+#              #
#    Updated: 2022/11/30 12:34:34 by kle-guen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
LIBFT = Libft/libft.a
CC = @gcc
CFLAGS = -g -Wall -Wextra -Werror -I includes
LFLAGS = -L/usr/local/lib -I/usr/local/include -lreadline
SRCS = srcs/main.c \
	   srcs/parsing/verif.c \
	   srcs/parsing/parsing.c \
	   srcs/parsing/parsing_2.c \
	   srcs/parsing/parsing_utils.c \
	   srcs/parsing/parsing_utils_2.c \
	   srcs/parsing/parsing_utils_3.c \
	   srcs/built_ins/built_ins.c \
	   srcs/built_ins/built_ins_2.c \
	   srcs/built_ins/built_ins_utils.c \
	   srcs/built_ins/built_ins_utils_2.c \
	   srcs/built_ins/built_ins_utils_3.c \
	   srcs/built_ins/built_ins_utils_4.c \
	   srcs/built_ins/built_ins_utils_5.c \
	   srcs/execution/exec_built.c \
	   srcs/execution/set_cmd_fd.c \
	   srcs/execution/cmds_init.c \
	   srcs/execution/cmd_not_found.c \
	   srcs/execution/execute_multiple_cmd.c \
	   srcs/execution/execute_one_cmd.c \
	   srcs/execution/execute_utils.c \
	   srcs/execution/execute_utils2.c \
	   srcs/execution/path_fonctions/get_path.c \
	   srcs/execution/path_fonctions/get_path_utils.c \
	   srcs/execution/here_doc.c \
	   srcs/execution/here_doc_utils.c \
	   srcs/execution/parse_input.c \
	   srcs/execution/print_error.c \
	   srcs/execution/redirections.c \
	   srcs/execution/setup_cmd.c \
	   srcs/execution/setup_cmd_utils.c \
	   srcs/execution/check_after_parsing2.c \
	   srcs/execution/check_after_parsing.c \
	   srcs/utils/create_env_list.c \
	   srcs/utils/strlen_utils.c \
	   srcs/utils/strlen_utils_2.c \
	   srcs/utils/free.c \
	   srcs/utils/utils.c \
	   srcs/exit.c

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
