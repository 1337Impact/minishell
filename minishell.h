/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:32:40 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/16 17:54:20 by tnamir           ###   ########.fr       */
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
# include <fcntl.h>

typedef struct s_minishell
{
	int		exita;
	char	*prompt;
	char	current_dir[1000];
	char	**options;
	char	**local_env;
	char	**env;
	int		exit_status;
	int		w_fd;
	int		r_fd;
	int		p;
}	t_minishell;

void	execute(char *cmd, t_minishell *minish, char	**argv);
char	f_or_d(char *input);
char	*rm_late_sp(char	*s);
char	*rm_early_sp(char	*s);
char	**quotes_presence(char	*input, t_minishell	*minish);
char	*quotes_handler(char *str, t_minishell *minish);
int		count_cmds(char *input);
char	*var_handler(char *buff, char *str, t_minishell *minish, int *x);
char	**cpy_it(char	*input, char	**options);
char	*ft_charjoin(char	*str, char c);
void	conditions(t_minishell *minishell, char	*input);
void	twod_free(char	**array);

// builtins commands
void	env(char	**env, t_minishell *minish);
void	echo(char	**options, t_minishell *minish);
void	cd(char *path, t_minishell *minish);
int		is_var(char	**local_env, char *var);
char	**unset_var(char *var_name, char **local_env);
char	**export(char	**local_env, t_minishell *minish);
char	**unset(char	**local_env, t_minishell *minish);
void	ft_exit(t_minishell *minishell);

// metacharachters
int		metacharacters(char *input, t_minishell *minish);
int		pipe_hand(t_minishell *minish, char *input, int x);
int		redirections_check(t_minishell *minish);
int		check_metacharacters(char *input);
char	*redirect_output(t_minishell *minish, char *input, int x);
char	*redirect_input(t_minishell *minish, char *input, int x);
char	*redirect_append(t_minishell *minish, char *input, int x);
char	*delimiter_input(t_minishell *minish, char *input, int x);

char	*output(t_minishell *minish, char *input, int x);

// error handler
void	print_error(char *str1, char *str2, t_minishell *minish, int val);
void	errory(t_minishell *minish);

// utils
void	print_export(t_minishell *minish);
char	*var_value(char	*str, char	**env);
char	*var_name_func(char *var);
char	*one_file_input(char	*input);
char	*who_file(char *input, t_minishell *minish);

#endif