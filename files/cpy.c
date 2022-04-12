/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:39:20 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/09 09:06:52 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	void	passing_stuff(int	*x, int	*sub_size, char *input);

static void	from_norm_to_quote(int	*x, int	*sub_size, char *input)
{
	while (input[*x] && input[*x] != ' ')
	{
		*x += 1;
		*sub_size += 1;
		if (input[*x] == '\"' || input[*x] == '\"')
			passing_stuff(x, sub_size, input);
	}
}

static	void	passing_stuff(int	*x, int	*sub_size, char *input)
{
	if (input[*x] == '\'')
	{
		*x += 1;
		*sub_size += 1;
		while (input[*x] && input[*x] != '\'')
		{
			*x += 1;
			*sub_size += 1;
		}
	}
	else if (input[*x] == '\"')
	{
		*x += 1;
		*sub_size += 1;
		while (input[*x] && input[*x] != '\"')
		{
			*x += 1;
			*sub_size += 1;
		}
	}
	from_norm_to_quote(x, sub_size, input);
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
