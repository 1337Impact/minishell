/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:55:03 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/29 13:03:16 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_check(char *input, int *x)
{
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

static void	fd_builder(t_minishell *minish, int *rd, int fd[2])
{
	if (minish->p < 2)
		minish->p += 1;
	if (!rd)
		*rd = fd[0];
	else
	{
		minish->r_fd = *rd;
		*rd = fd[0];
	}
	minish->w_fd = fd[1];
}

static void	last_pars(t_minishell *minish, char	*str, int rd)
{
	minish->w_fd = 1;
	minish->r_fd = rd;
	minish->p = 3;
	conditions(minish, rm_early_sp(rm_late_sp(str)));
	close(rd);
	free(str);
}

static int	pipe_pars(t_minishell *minish, char	*input)
{
	int		x;
	int		start;
	char	*str;
	int		fd[2];
	int		rd;

	x = 0;
	start = 0;
	rd = 0;
	while (pipe_check(input, &x) == 1)
	{
		if (pipe(fd) == -1)
			return (2);
		fd_builder(minish, &rd, fd);
		str = ft_substr(input, start, x - start);
		conditions(minish, rm_early_sp(rm_late_sp(str)));
		close(minish->w_fd);
		if (!rd)
			close(rd);
		x++;
		start = x;
		free(str);
	}
	last_pars(minish, ft_substr(input, start, x - start), rd);
	return (1);
}

int	pipe_hand(t_minishell *minish, char	*input)
{
	int		x;

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
	return (pipe_pars(minish, input));
}
