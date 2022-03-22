/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:30:16 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/22 16:34:27 by tnamir           ###   ########.fr       */
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
		printf("%s\n", minishell->current_dir);
	else if (!ft_strncmp(minishell->options[0], "cd", 3))
		chdir(minishell->options[1]);
	else if (!ft_strncmp(minishell->options[0], "echo", 5))
		echo(minishell->options);
	else if (f_or_d(minishell->options[0]) == 'f')
		execute(minishell->options[0], envp, minishell, minishell->options);
	else if (f_or_d(minishell->options[0]) == 'd')
		chdir(minishell->options[0]);
	else
	{
		printf("minishell: command not found %s\n", input);
		minishell->prompt = RED"👹 Minishell ➤\033[0m";
		// printf ("%so\n", minishell->options[0]);
	}
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
	minishell.prompt = CYAN"💀 Minishell ➤\033[0m";
	while (!minishell.exita)
	{
		getcwd(minishell.current_dir, 200);
		input = readline(minishell.prompt);
		if (!input)
			break ;
		if (input[0] == '\0' || !tab_sp_check(input))
			continue ;
		if (add_history(input))
			perror("error ");
		conditions(&minishell, input, envp);
		free(input);
	}	
	return (0);
}
