# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbenkhat <mbenkhat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 16:38:27 by tnamir            #+#    #+#              #
#    Updated: 2022/03/25 13:43:12 by mbenkhat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#								  -*-Makefile-*-							   #

HEADER = minishell.h

FLAGS = -Wall -Wextra -Werror

SRC = main.c ./files/execute.c ./files/f_or_d.c ./files/sp_remover.c ./files/quotes_handler.c ./files/builtins_cmds.c ./files/utils.c ./files/env_var.c ./files/cpy.c ./files/unset_export.c

NAME = minishell

LIBFT = ./libft/libft.a

OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	@cc $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

%.o: %.c $(HEADER)
	@cc $(FLAGS) -c -o $@ $<

$(LIBFT) :
	@$(MAKE) -C ./libft

clean :
	@rm -rf ./libft/*.o $(OBJS)

fclean : clean
	@rm -rf $(LIBFT) $(NAME)

re : fclean all

c : all clean
	./minishell

.PHONY : clean fclean re

#								  -*-Makefile-*-							   #