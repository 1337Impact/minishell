/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 16:05:27 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/11 16:05:27 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_hand(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
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

static void	wanna_be_main(t_minishell *minishell)
{
	char	*input;

	while (!minishell->exita)
	{
		minishell->r_fd = 0;
		minishell->w_fd = 1;
		minishell->p = 0;
		getcwd(minishell->current_dir, 1000);
		if (minishell->exit_status)
			minishell->prompt = RED"👹 Minishell ➤\033[0m";
		input = readline(minishell->prompt);
		if (!input)
		{
			ft_putstr_fd(RED"\b\b  exit 💀\033[0m", 1);
			break ;
		}
		if (tab_sp_check(input))
		{
			add_history(input);
			if (!metacharacters(input, minishell))
				conditions(minishell, input);
		}
		free(input);
	}
}

int	main(int c, char **v, char **envp)
{
	t_minishell		minishell;
	int				i;

	(void)c;
	(void)v;
	signal(SIGINT, sig_hand);
	signal(SIGQUIT, sig_hand);
	minishell.env = envp;
	minishell.local_env = malloc((twod_array_len(envp) + 1) * sizeof(char *));
	i = -1;
	while (envp[++i])
		minishell.local_env[i] = ft_strdup(envp[i]);
	minishell.local_env[i] = NULL;
	minishell.prompt = CYAN"💀 Minishell ➤\033[0m";
	minishell.exit_status = 0;
	minishell.p = 0;
	wanna_be_main(&minishell);
	twod_free(minishell.local_env);
	exit(minishell.exit_status);
}
