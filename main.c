/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 16:30:16 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/02 18:46:12 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_prompt(void);

int	g_sig = 0;

static int	tab_sp_check(char	*input)
{
	int	x;

	x = -1;
	while (input[++x])
		if (input[x] != ' ' && input[x] != '\t')
			return (1);
	return (0);
}

static void	more_conditions(t_minishell *minishell)
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
		execute(minishell->options[0], minishell, minishell->options);
}

void	conditions(t_minishell *minishell,
	char	*input)
{
	input = rm_early_sp(rm_late_sp(input));
	minishell->options = quotes_presence(input, minishell);
	minishell->prompt = CYAN"💀 Minishell ➤\033[0m";
	if (!ft_strncmp(minishell->options[0], "exit", 5))
		minishell->exita = 1;
	else if (!ft_strncmp(minishell->options[0], "pwd", 4))
	{
		ft_putendl_fd(minishell->current_dir, minishell->w_fd);
		minishell->exit_status = 0;
	}
	else
		more_conditions(minishell);
	twod_free(minishell->options);
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

void	sig_hand(int sig)
{
	if (sig == SIGINT)
	{
		if (g_sig == 0)
		{
			ft_putchar_fd('\n', 1);
			ft_putstr_fd(RED"💀 Minishell ➤\033[0m", 1);
		}
		// if (g_sig == 1)
		// {
		// 	ft_putstr_fd("\b\b", 1);
		// }
	}
}

int	init_prompt(void)
{
	t_minishell		minishell;
	int				i;
	extern char** 	environ;

	g_sig = 0;
	minishell.local_env = malloc((twod_array_len(environ) + 1) * sizeof(char *));
	i = -1;
	while (environ[++i])
		minishell.local_env[i] = ft_strdup(environ[i]);
	minishell.local_env[i] = 0;
	minishell.prompt = CYAN"💀 Minishell ➤\033[0m";
	minishell.exit_status = 0;
	minishell.p = 0;
	wanna_be_main(&minishell);
	twod_free(minishell.local_env);
	return (minishell.exit_status);
}

int	main()
{
	signal(SIGINT, sig_hand);
	init_prompt();
	return (0);
}
