/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:30:16 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/03 14:06:47 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

void	sig_hand(int sig)
{
	if (sig == SIGINT)
	{
		if (g_sig == 0)
		{
			ft_putchar_fd('\n', 1);
			ft_putstr_fd(RED"💀 Minishell ➤\033[0m", 1);
			g_sig = 1;
		}
		else
		{
			ft_putstr_fd("\b\b  \n", 1);
			ft_putstr_fd(RED"💀 Minishell ➤\033[0m", 1);
		}
	}
	else if (sig == SIGQUIT)
		write(1, "SIGLOL\n", 8);
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
		input = rm_early_sp(rm_late_sp(input));
		if (!metacharacters(input, minishell))
			conditions(minishell, input);
		free(input);
	}
}


int	main(int c, char **v, char **envp)
{
	t_minishell		minishell;
	int				i;

	(void)c;
	(void)v;
	g_sig = 0;
	signal(SIGINT, sig_hand);
	signal(SIGQUIT, SIG_IGN);
	minishell.local_env = malloc((twod_array_len(envp) + 1) * sizeof(char *));
	i = -1;
	while (envp[++i])
		minishell.local_env[i] = ft_strdup(envp[i]);
	minishell.local_env[i] = 0;
	minishell.prompt = CYAN"💀 Minishell ➤\033[0m";
	minishell.exit_status = 0;
	minishell.p = 0;
	wanna_be_main(&minishell);
	twod_free(minishell.local_env);
	return (minishell.exit_status);
}
