/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:30:16 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/24 18:43:35 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else if (!ft_strncmp(minishell->options[0], "cd", 3))
		cd(minishell->options[1], minishell);
	else if (!ft_strncmp(minishell->options[0], "echo", 5))
		echo(minishell->options, minishell);
	else if (!ft_strncmp(minishell->options[0], "env", 4))
		env(envp, minishell);
	else if (f_or_d(minishell->options[0]) == 'd')
		cd(minishell->options[0], minishell);
	else if (!ft_strncmp(minishell->options[0], "export", 7))
		export(minishell, minishell->options[1]);
	else
		execute(minishell->options[0], envp, minishell, minishell->options);
}

static int	tab_sp_check(char	*input)
{
	int	x;

	x = -1;
	while (input[++x])
		if (input[x] != ' ' && input[x] != '\t')
			return (1);
	return (0);
}

int	main(int c, char **v, char **envp)
{
	char		*input;
	t_minishell	minishell;

	(void)c;
	(void)v;
	minishell.env = envp;
	minishell.new_env = envp;
	minishell.prompt = CYAN"💀 Minishell ➤\033[0m";
	minishell.exit_status = 0;
	while (!minishell.exita)
	{
		getcwd(minishell.current_dir, 200);
		if (minishell.exit_status)
			minishell.prompt = RED"👹 Minishell ➤\033[0m";
		input = readline(minishell.prompt);
		if (!input)
			break ;
		if (!tab_sp_check(input))
			continue ;
		if (add_history(input))
			perror("error ");
		conditions(&minishell, input, envp);
		free(input);
	}	
	return (0);
}
