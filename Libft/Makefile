# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chjoie <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 14:03:08 by chjoie            #+#    #+#              #
#    Updated: 2022/04/15 17:57:13 by chjoie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_putnbr_fd.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memcpy.c ft_memset.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_tolower.c ft_toupper.c ft_memmove.c ft_strlcat.c ft_strchr.c ft_strrchr.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c

SRCSB	= ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJSB	= ${SRCSB:.c=.o}

OBJS    = ${SRCS:.c=.o}


NAME	= libft.a

CC	= gcc

RM	= rm -f

CFLAGS = -Wall -Werror -Wextra -I.libft.h

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
	ar rcs ${NAME} ${OBJS}

all:	${NAME}

clean:
	${RM} ${OBJS} ${OBJSB}

fclean:	clean
	${RM} ${NAME}

re: fclean all

bonus: $(OBJSB)
	ar rcs ${NAME} ${OBJSB}

.PHONY:	all clean fclean re bonus
