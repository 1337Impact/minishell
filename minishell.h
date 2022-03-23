/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:32:40 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/23 18:39:44 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define RED "\033[0;31m"
# define CYAN "\033[0;36m"

# include "./libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

typedef struct s_minishell
{
	int		exita;
	char	*prompt;
	char	current_dir[200];
	char	**options;
	char	**env;
	int		exit_status;
}	t_minishell;

void	execute(char *input, char **envp, t_minishell *minishell, char	**argv);
char	f_or_d(char *input);
char	*rm_late_sp(char	*s);
char	*rm_early_sp(char	*s);
char	**quotes_presence(char	*input, t_minishell	*minish);
void	echo(char	**options);
int		count_cmds(char *input);
char	*var_handler(char *buff, char *str, t_minishell *minish, int *x);
void	env_print(char	**env);
char	**cpy_it(char	*input, char	**options);

#endif