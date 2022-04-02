/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:39:20 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/02 17:09:12 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	passing_stuff(int	*x, int	*sub_size, char *input)
{
	if (input[*x] == '\'')
	{
		*x += 1;
		*sub_size += 1;
		while (input[*x] != '\'' && input[*x])
		{
			*x += 1;
			*sub_size += 1;
		}
	}
	else if (input[*x] == '\"')
	{
		*x += 1;
		*sub_size += 1;
		while (input[*x] != '\"' && input[*x])
		{
			*x += 1;
			*sub_size += 1;
		}
	}
	while (input[*x] != ' ' && input[*x])
	{
		*x += 1;
		*sub_size += 1;
	}
}

char	**cpy_it(char	*input, char	**options)
{
	int	x;
	int	y;
	int	size;
	int	sub_size;
	int	start;

	size = count_cmds(input);
	options = ft_calloc(size + 1, sizeof(char *));
	x = 0;
	y = -1;
	while (++y < size)
	{
		start = x;
		sub_size = 0;
		passing_stuff(&x, &sub_size, input);
		while (input[x] == ' ')
			x++;
		options[y] = ft_substr(input, start, sub_size);
	}
	return (options);
}
