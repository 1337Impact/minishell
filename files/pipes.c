/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenkhat <mbenkhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:55:03 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/29 09:48:37 by mbenkhat         ###   ########.fr       */
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
	int		rd;

	x = 0;
	input = rm_early_sp(rm_late_sp(input));
	if (!pipe_check(input, &x))
		return (0);
	if (pipe_check(input, &x) == 2)
	{
		ft_putendl_fd("minishell: parse error near `|\'", 2);
		minish->exit_status = 1;
		return (1);
	}
	x = 0;
	start = 0;
	rd = 0;
	while (pipe_check(input, &x) == 1)
	{
		if (pipe(fd) == -1)
			return (2);
		if (minish->p < 2)
			minish->p += 1;
		if (!rd)
			rd = fd[0];
		else
		{
			minish->r_fd = rd;
			rd = fd[0];
		}
		minish->w_fd = fd[1];
		str = ft_substr(input, start, x - start);
		conditions(minish, rm_early_sp(rm_late_sp(str)));
		close(minish->w_fd);
		if (!rd)
			close(rd);
		x++;
		start = x;
		free(str);
	}
	minish->w_fd = 1;
	minish->r_fd = rd;
	minish->p = 3;
	str = ft_substr(input, start, x - start);
	conditions(minish, rm_early_sp(rm_late_sp(str)));
	close(rd);
	free(str);
	return (1);
}
