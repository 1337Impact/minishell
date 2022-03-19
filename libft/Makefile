# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/23 14:41:24 by tnamir            #+#    #+#              #
#    Updated: 2022/03/18 11:59:43 by tnamir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -*- Makefile -*-

NAME = libft.a

HEADER = libft.h

FCTS 	=	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
			ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c \
			ft_strchr.c ft_strtrim.c ft_split.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
			ft_strdup.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_putstr_fd.c \
			ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_substr.c ft_tolower.c ft_toupper.c \
			ft_putendl_fd.c ft_putnbr_fd.c ft_2d_array_len.c \

BONUSFCTS =	ft_lstnew.c ft_lstsize.c ft_lstadd_back.c ft_lstadd_front.c ft_lstlast.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \

OBJBONUS = $(BONUSFCTS:.c=.o)

OBJ		= $(FCTS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	@ar -rc $@ $^

%.o: %.c
	@gcc -Wall -Werror -Wextra -c $<

clean:
	@rm -f $(OBJ) $(OBJBONUS)

fclean: clean
	@rm -f $(NAME)

bonus: $(OBJ) $(OBJBONUS) $(HEADER)
	@ar cr $(NAME) $(OBJ) $(OBJBONUS)

re: fclean all

.PHONY: clean fclean bonus re