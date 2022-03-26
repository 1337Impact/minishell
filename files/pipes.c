/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenkhat <mbenkhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:55:03 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/26 18:08:37 by mbenkhat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_check(char *input, int *x)
{
	int	q_c;

	q_c = 0;
	if (input[0] == '|') 
		return (2);
	while (input[*x])
	{
		if (input[*x] == '\"')
		{
			*x += 1;
			while (input[*x] != '\"')
				*x += 1;
		}
		else if (input[*x] == '\'')
		{
			*x += 1;
			while (input[*x] != '\'')
				*x += 1;
		}
		else if (input[*x] == '|')
			return (1);
		*x += 1;
	}
	return (0);
}

int	pipe_hand(t_minishell *minish, char	*input)
{
	int		x;
	int		start;
	char	*str;
	int		fd[2];

	x = 0;
	input = rm_early_sp(rm_late_sp(input));
	if (!pipe_check(input, &x))
		return (0);
	if (pipe_check(input, &x) == 2)
	{
		ft_putendl_fd("zsh: parse error near `|\'", 2);
		minish->exit_status = 1;
		return (1);
	}
	////////////////

	if (pipe(fd) == -1)
		return (1);
	dup2(fd[1], 1);
	str = ft_substr(input, 0, x);
	str = rm_early_sp(str);
	conditions(minish, str, minish->local_env);
	free(str);
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	start = ++x;
	pipe_check(input, &x);
	str = ft_substr(input, start, x);
	str = rm_early_sp(str);
	conditions(minish, str, minish->local_env);
	
	/////////////////
	return (1);
}
