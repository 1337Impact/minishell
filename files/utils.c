/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:41:40 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/11 23:46:10 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmds(char *input)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (input[++i])
	{
		if (input[i] == ' ')
			counter++;
		while (input[i] == ' ')
			i++;
		if (input[i] == '\"')
		{
			i++;
			while (input[i] != '\"' && input[i])
				i++;
		}
		if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'' && input[i])
				i++;
		}
	}
	return (++counter);
}

void	twod_free(char	**array)
{
	int	x;

	x = -1;
	while (array[++x])
		free(array[x]);
	free(array);
}

void	print_error(char *str1, char *str2, t_minishell *minish, int val)
{
	if (str2)
	{
		ft_putstr_fd(str1, 2);
		ft_putendl_fd(str2, 2);
	}
	else
		ft_putendl_fd(str1, 2);
	minish->exit_status = val;
}

void	cpy_print_export(t_minishell *minish, int x, int y, int *equal)
{
	if (minish->local_env[y][x - 1] == '=')
	{
		ft_putchar_fd('\"', minish->w_fd);
		*equal = 1;
	}
	ft_putchar_fd(minish->local_env[y][x], minish->w_fd);
}

void	print_export(t_minishell *minish)
{
	int		y;
	int		x;
	int		equal;

	y = -1;
	while (minish->local_env[++y])
	{
		equal = 0;
		x = 0;
		ft_putstr_fd("declare -x ", minish->w_fd);
		while (minish->local_env[y][x])
		{
			cpy_print_export(minish, x, y, &equal);
			x++;
		}
		if (minish->local_env[y][x - 1] == '=')
		{
			ft_putchar_fd('\"', minish->w_fd);
			equal = 1;
		}
		if (equal)
			ft_putchar_fd('\"', minish->w_fd);
		ft_putchar_fd('\n', minish->w_fd);
	}
}
