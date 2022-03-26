/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:30:16 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/26 13:06:56 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tab_sp_check(char	*input)
{
	int	x;

	x = -1;
	while (input[++x])
		if (input[x] != ' ' && input[x] != '\t')
			return (1);
	return (0);
}

static void	more_conditions(t_minishell *minishell, char **envp)
{
	if (!ft_strncmp(minishell->options[0], "cd", 3))
		cd(minishell->options[1], minishell);
	else if (!ft_strncmp(minishell->options[0], "echo", 5))
		echo(minishell->options, minishell);
	else if (!ft_strncmp(minishell->options[0], "env", 4))
		env(minishell->local_env, minishell);
	else if (!ft_strncmp(minishell->options[0], "export", 7))
		minishell->local_env = export(minishell->local_env, minishell);
	else if (!ft_strncmp(minishell->options[0], "unset", 5))
		minishell->local_env = unset(minishell->local_env, minishell);
	else if (f_or_d(minishell->options[0]) == 'd')
		cd(minishell->options[0], minishell);
	else
	{
		execute(minishell->options[0], envp, minishell, minishell->options);
	}
}

void	conditions(t_minishell *minishell,
	char	*input, char **envp)
{
	(void)envp;
	input = rm_early_sp(rm_late_sp(input));
	minishell->options = quotes_presence(input, minishell);
	minishell->prompt = CYAN"💀 Minishell ➤\033[0m";
	if (!ft_strncmp(minishell->options[0], "exit", 5))
		minishell->exita = 1;
	else if (!ft_strncmp(minishell->options[0], "pwd", 4))
	{
		printf("%s\n", minishell->current_dir);
		minishell->exit_status = 0;
	}
	else
		more_conditions(minishell, envp);
}

static void	wanna_be_main(t_minishell *minishell, char	**envp)
{
	char	*input;

	while (!minishell->exita)
	{
		getcwd(minishell->current_dir, 200);
		if (minishell->exit_status)
			minishell->prompt = RED"👹 Minishell ➤\033[0m";
		input = readline(minishell->prompt);
		if (!input)
			break ;
		if (!tab_sp_check(input))
			continue ;
		if (add_history(input))
			perror("error ");
		pipe_hand(minishell, input);
		conditions(minishell, input, envp);
		free(input);
	}
}

int	main(int c, char **v, char **envp)
{
	t_minishell	minishell;
	int			i;

	(void)c;
	(void)v;
	minishell.local_env = malloc((twod_array_len(envp) + 1) * sizeof(char *));
	i = -1;
	while (envp[++i])
		minishell.local_env[i] = ft_strdup(envp[i]);
	minishell.local_env[i] = 0;
	minishell.prompt = CYAN"💀 Minishell ➤\033[0m";
	minishell.exit_status = 0;
	wanna_be_main(&minishell, envp);
	return (0);
}
