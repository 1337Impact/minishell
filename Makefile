# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 16:38:27 by tnamir            #+#    #+#              #
#    Updated: 2022/03/19 15:50:34 by tnamir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#								  -*-Makefile-*-							   #

HEADER = minishell.h

SRC = main.c ./files/execute.c ./files/f_or_d.c ./files/sp_remover.c

NAME = minishell

LIBFT = ./libft/libft.a

all : $(NAME)


$(NAME) : $(SRC) $(UTILSRC) $(LIBFT)
	@cc -Wall -Wextra -Werror $(SRC) $(LIBFT) -o $(NAME) -lreadline

$(LIBFT) :
	@$(MAKE) -C ./libft

clean :
	@rm -rf $(NAME) ./libft/*.o

fclean : clean
	@rm -rf $(LIBFT)

re : fclean all

.PHONY : clean fclean re

#								  -*-Makefile-*-							   #