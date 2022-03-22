/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:29:23 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/21 21:07:56 by tnamir           ###   ########.fr       */
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
			while ((input[i] != '\'' && input[i] != '\"') && input[i])
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
	options = ft_calloc(size + 1, sizeof(char *));
	x = 0;
	y = -1;
	while (++y < size)
	{
		start = x;
		sub_size = 0;
// if open quote is found skip everythings in between till close quote is found and add that to OPTIONS
		if (input[x] == '\'')
		{
			x++;
			while (input[x] != '\'' && input[x])
			{
				x++;
				sub_size++;
			}
		}
		if (input[x] == '\"')
		{
			x++;
			while (input[x] != '\"' && input[x])
			{
				x++;
				sub_size++;
			}
		}
// if there isn't any space after closing quote it'll be added in the same string
		if (input[x] != ' ')
		{
			while (input[x] != ' ' && input[x])
			{
				x++;
				sub_size++;
			}
		}
		while (input[x] == ' ')
			x++;
		options[y] = ft_substr(input, start, sub_size);
	}
	return (options);
}

char	*quotes_handler(char *str, int type)
{
// delete quotes from string + handle variales
	char	*buff;
	int		i;
	int		x;

	buff = ft_calloc(ft_strlen(str) + 1, 1);
	i = 0;
	x = 0;
	while(str[x])
	{
		if (str[x] == '\'' || str[x] == '\"')
			x++;
		if (!str[x])
			break ;
		if (str[x] == '$' && type)
		{
			//handling variables
		}
		buff[i] = str[x];
		i++;
		x++;
	}
	free (str);
	return (buff);
}

char	**quotes_presence(char	*input, char **options)
{
	int	i;

	i = -1;
	options = cpy_it(input, options);
	// while (options[++i])
	// 	printf("%s ----  ", options[i]);
	while (options[++i])
	{
		if (ft_strchr(options[i], '\"'))
			options[i] = quotes_handler(options[i], 1);
		else if (ft_strchr(options[i], '\''))
			options[i] = quotes_handler(options[i], 0);
		printf("%s\n", options[i]);
	}
	return (options);
}
