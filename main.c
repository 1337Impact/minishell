/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:30:16 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/21 18:14:59 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	conditions(t_minishell *minishell,
	char	*input, char **envp)
{
	char	**options;

	minishell->options = ft_calloc(100, sizeof(char *));
	options = minishell->options;
	input = rm_early_sp(rm_late_sp(input));
	if (ft_strchr(input, '\"') || ft_strchr(input, '\''))
		options = quotes_presence(input);
	else
		minishell->options = ft_split(input, ' ');
	minishell->prompt = CYAN"💀 Minishell ➤\033[0m";
	if (!ft_strncmp(input, "exit", 5))
		minishell->exita = 1;
	else if (!ft_strncmp(input, "pwd", 4))
		printf("%s\n", minishell->current_dir);
	else if (!ft_strncmp("cd", input, 2))
		chdir(rm_early_sp(input + 2));
	else if (f_or_d(options[0]) == 'f')
		execute(options[0], envp, minishell, options);
	else if (f_or_d(options[0]) == 'd')
		chdir(options[0]);
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
