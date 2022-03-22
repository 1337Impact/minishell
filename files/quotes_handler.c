/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:29:23 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/22 17:30:25 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

static	char	**cpy_it(char	*input, char	**options)
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


char	*quotes_handler(char *str, int type, char **env)
{
	char	*buff;
	int		i;
	int		x;
	int		env_size;

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
			x++;
			i = -1;
			env_size = twod_array_len(env);
			while (++i < env_size)
			{
				if (!ft_strncmp(env[i], str + x, ft_strlen(str + x))
						&& env[i][ft_strlen(str + x)] == '=')
				{
					str[x - 1] = 0;
					return (ft_strjoin(str, env[i] + ft_strlen(str + x) + 1));
				}
			}
		}
		buff[i] = str[x];
		i++;
		x++;
	}
	free (str);
	return (buff);
}

char	**quotes_presence(char	*input, t_minishell	*minish)
{
	int	i;

	i = -1;
	minish->options = cpy_it(input, minish->options);
	while (minish->options[++i])
	{
		if (ft_strchr(minish->options[i], '\''))
			minish->options[i] = quotes_handler(minish->options[i],
					0, minish->env);
		else
			minish->options[i] = quotes_handler(minish->options[i],
					1, minish->env);
	}
	return (minish->options);
}
