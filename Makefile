# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/15 16:38:27 by tnamir            #+#    #+#              #
#    Updated: 2022/04/18 22:53:11 by tnamir           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#								  -*-Makefile-*-							   #

RED='\033[0;31m'

HEADER = minishell.h

FLAGS = -Wall -Werror -Wextra -L$(shell brew --prefix readline)/lib -I$(shell brew --prefix readline)/include -lreadline

SRC = main.c ./files/execute.c ./files/f_or_d.c ./files/sp_remover.c ./files/quotes_handler.c ./files/builtins_cmds.c \
 ./files/utils.c ./files/env_var.c ./files/cpy.c ./files/export.c ./files/unset.c ./files/pipes.c ./files/redirections.c \
 ./files/metacharacters.c ./files/conditions.c ./files/utils2.c

NAME = minishell

LIBFT = ./libft/libft.a

all : $(NAME)

$(NAME)	:	$(HEADER) $(SRC) $(LIBFT)
	@cc $(FLAGS) $(SRC) $(LIBFT) -lreadline -o $(NAME)

	@echo ${RED}" __  __ _       _     _          _ _ "
	@echo ${RED}"|  \/  (_)_ __ (_)___| |__   ___| | |"
	@echo ${RED}"| |\/| | | '_ \| / __| '_ \ / _ \ | |"
	@echo ${RED}"| |  | | | | | | \__ \ | | |  __/ | |"
	@echo ${RED}"|_|  |_|_|_| |_|_|___/_| |_|\___|_|_|1337"

$(LIBFT) :
	@$(MAKE) -C ./libft

clean :
	@rm -rf ./libft/*.o

fclean : clean
	@rm -rf $(LIBFT) $(NAME)

re : fclean all

.PHONY : clean fclean re

#								  -*-Makefile-*-							   #