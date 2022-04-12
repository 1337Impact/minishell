/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 13:45:57 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/12 15:16:53 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	more_conditions(t_minishell *minishell)
{
	if (!ft_strncmp(minishell->options[0], "cd", 3))
		cd(minishell->options[1], minishell);
	else if (!ft_strncmp(minishell->options[0], "echo", 5))
		echo(minishell->options, minishell);
	else if (!ft_strncmp(minishell->options[0], "env", 4))
		env(minishell->env, minishell);
	else if (!ft_strncmp(minishell->options[0], "export", 7))
		minishell->local_env = export(minishell->local_env, minishell);
	else if (!ft_strncmp(minishell->options[0], "unset", 5))
		minishell->local_env = unset(minishell->local_env, minishell);
	else if (f_or_d(minishell->options[0]) == 'd')
		cd(minishell->options[0], minishell);
	else if (minishell->options[0][0] != '\0')
		execute(minishell->options[0], minishell, minishell->options);
	else
		errory(minishell);
}

void	conditions(t_minishell *minishell,
	char	*input)
{
	minishell->options = quotes_presence(input, minishell);
	minishell->prompt = CYAN"💀 Minishell ➤\033[0m";
	if (!ft_strncmp(minishell->options[0], "exit", 5))
		ft_exit(minishell);
	else if (!ft_strncmp(minishell->options[0], "pwd", 4))
	{
		ft_putendl_fd(minishell->current_dir, minishell->w_fd);
		minishell->exit_status = 0;
	}
	else
		more_conditions(minishell);
	twod_free(minishell->options);
}
