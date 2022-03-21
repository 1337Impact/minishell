/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:29:23 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/21 20:35:33 by tnamir           ###   ########.fr       */
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
		if (input[i] == '\'' || input[i] == '\"')
		{
			i++;
			while (input[i] != '\'' && input[i] != '\"')
				i++;
		}
	}
	return (++counter);
}

static	char	**cpy_it(char	*input, char **options)
{
	int	x;
	int	y;
	int	size;
	int	sub_size;
	int	start;

	size = count_cmds(input);
	options = ft_calloc(size, sizeof(char *));
	x = 0;
	y = -1;
	while (++y < size)
	{
		start = x;
		sub_size = 0;
		while (input[x] != ' ' && input[x])
		{
			x++;
			sub_size++;
		}
		while (input[x] == ' ' && input[x])
			x++;
		options[y] = ft_substr(input, start, sub_size);
	}
	return (options);
}

// static void	quote(char	*input, char	**options)
// {
// 	int	x;
// 	int	y;

// 	x = -1;
// 	y = 0;
// 	while (input[++x])
// 	{
// 		if (input[x] == '\'')
// 			;
// 		printf("%s\n", ft_substr(options[y], x, cpy_till_char(input, ' ')));
// 		y++;
// 	}
// 	return ;
// }

void	quotes_presence(char	*input, char **options)
{
	options = cpy_it(input, options);
	printf("%s", options[1]);
}
