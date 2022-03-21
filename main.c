/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:30:16 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/21 21:07:39 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	conditions(t_minishell *minishell,
	char	*input, char **envp)
{
	(void)envp;
	input = rm_early_sp(rm_late_sp(input));
	minishell->options = quotes_presence(input, minishell->options);
	minishell->prompt = CYAN"💀 Minishell ➤\033[0m";
	if (!ft_strncmp(input, "exit", 5))
		minishell->exita = 1;
	else if (!ft_strncmp(input, "pwd", 4))
		printf("%s\n", minishell->current_dir);
	else if (!ft_strncmp("cd", input, 2))
		chdir(rm_early_sp(input + 2));
	else if (f_or_d(minishell->options[0]) == 'f')
		execute(minishell->options[0], envp, minishell, minishell->options);
	else if (f_or_d(minishell->options[0]) == 'd')
		chdir(minishell->options[0]);
	else
	{
		printf("minishell: command not found %s\n", input);
		minishell->prompt = RED"👹 Minishell ➤\033[0m";
	}
}

int	main(int c, char **v, char **envp)
{
	char		*input;
	t_minishell	minishell;

	(void)c;
	(void)v;
	minishell.prompt = CYAN"💀 Minishell ➤\033[0m";
	while (!minishell.exita)
	{
		getcwd(minishell.current_dir, 200);
		input = readline(minishell.prompt);
		if (!input)
			break ;
		if (input[0] == '\0')
			continue ;
		if (add_history(input))
			perror("error ");
		conditions(&minishell, input, envp);
		free(input);
	}	
	return (0);
}
