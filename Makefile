# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 16:38:27 by tnamir            #+#    #+#              #
#    Updated: 2022/04/11 17:15:06 by tnamir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#								  -*-Makefile-*-							   #

HEADER = minishell.h

FLAGS = -L$(shell brew --prefix readline)/lib -I$(shell brew --prefix readline)/include -lreadline

SRC = main.c ./files/execute.c ./files/f_or_d.c ./files/sp_remover.c ./files/quotes_handler.c ./files/builtins_cmds.c \
 ./files/utils.c ./files/env_var.c ./files/cpy.c ./files/export.c ./files/unset.c ./files/pipes.c ./files/redirections.c \
 ./files/metacharacters.c ./files/conditions.c ./files/output.c

NAME = minishell

LIBFT = ./libft/libft.a

# OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	@cc $(FLAGS) $(SRC) $(LIBFT) -o $(NAME)

# %.o: %.c $(HEADER)
# 	@cc $(FLAGS) $(RL_FLAG) -c -o $@ $<

$(LIBFT) :
	@$(MAKE) -C ./libft

clean :
	@rm -rf ./libft/*.o $(OBJS)

fclean : clean
	@rm -rf $(LIBFT) $(NAME)

re : fclean all

.PHONY : clean fclean re

#								  -*-Makefile-*-							   #