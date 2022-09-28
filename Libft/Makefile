# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kle-guen <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/31 15:33:34 by kle-guen          #+#    #+#              #
#    Updated: 2022/04/13 17:04:27 by kle-guen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_atoi.c \
	   ft_isalpha.c \
	   ft_memchr.c \
	   ft_memset.c \
	   ft_strlen.c \
	   ft_tolower.c \
	   ft_bzero.c \
	   ft_isascii.c \
	   ft_memcmp.c \
	   ft_strchr.c \
	   ft_strncmp.c \
	   ft_toupper.c \
	   ft_calloc.c \
	   ft_isdigit.c \
	   ft_memcpy.c \
	   ft_strdup.c \
	   ft_strnstr.c \
	   ft_isalnum.c \
	   ft_isprint.c \
	   ft_memmove.c \
	   ft_strlcpy.c \
	   ft_strlcat.c \
	   ft_strrchr.c \
	   ft_itoa.c \
	   ft_putchar_fd.c \
	   ft_putendl_fd.c \
	   ft_putnbr_fd.c \
	   ft_putstr_fd.c \
	   ft_split.c \
	   ft_strjoin.c \
	   ft_strmapi.c \
	   ft_strtrim.c \
	   ft_striteri.c \
	   ft_substr.c \

SRCBS = ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
	
OBJS = $(SRCS:.c=.o)

BONUS = $(SRCBS:.c=.o)

CC = gcc 

RM = rm -f

CFLAGS = -Wall -Werror -Wextra

.c.o:
	$(CC) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
	ar rc $(NAME) $(OBJS)

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS) $(SRCBS)
	gcc -nostartfiles -shared -o libft.so $(OBJS) $(BONUS)

all: $(NAME)


bonus: $(BONUS) 
	 ar rc $(NAME) $(BONUS) 

clean: 
	$(RM) $(OBJS) $(BONUS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all 

.PHONY: all clean fclean re
