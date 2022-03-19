/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:30:16 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/19 17:29:23 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	conditions0(t_minishell *minishell,
	char	*input, char **envp, char **argv)
{
	(void)envp;
	input = rm_early_sp(rm_late_sp(input));
	minishell->prompt = CYAN"💀 Minishell ➤\033[0m";
	if (!ft_strncmp(input, "exit", 5))
		minishell->exita = 1;
	else if (f_or_d(input) == 'f')
		execute(input, envp, minishell, argv);
	else if (f_or_d(input) == 'd')
		chdir(input);
	else
	{
		printf("minishell: command not found: %s\n", input);
		minishell->prompt = RED"👹 Minishell ➤\033[0m";
	}
}

int	main(int c, char **v, char **envp)
{
	char		*input;
	t_minishell	minishell;

	(void)c;
	minishell.current_dir = getcwd(NULL, 0);
	minishell.prompt = CYAN"💀 Minishell ➤\033[0m";
	while (!minishell.exita)
	{
		input = readline(minishell.prompt);
		add_history(input);
		if (!input)
			break ;
		else
			if (c == 1)
				conditions0(&minishell, input, envp, v);
		free(input);
	}
	return (0);
}
