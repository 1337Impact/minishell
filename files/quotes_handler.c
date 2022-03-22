/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:29:23 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/22 15:42:22 by tnamir           ###   ########.fr       */
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

// if open quote is found skip everythings in between till close quote 
//is found and add that to OPTIONS
static	void	keep_cpying_it(int	*x, int	*sub_size, char *input)
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
		keep_cpying_it(&x, &sub_size, input);
		while (input[x] == ' ')
			x++;
		options[y] = ft_substr(input, start, sub_size);
	}
	return (options);
}

// delete quotes from string + handle variales
char	*quotes_handler(char *str, int type)
{
	char	*buff;
	int		i;
	int		x;

	buff = ft_calloc(ft_strlen(str) + 1, 1);
	i = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == '\'' || str[x] == '\"')
			x++;
		if (!str[x])
			break ;
		if (str[x] == '$' && type)
		{
			//handling variables
			write(1, "xD\n", 3);
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
	// 	printf("%s\n", options[i]);
	while (options[++i])
	{
		if (ft_strchr(options[i], '\''))
			options[i] = quotes_handler(options[i], 0);
		else
			options[i] = quotes_handler(options[i], 1);
	}
	return (options);
}
