/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:29:23 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/23 15:38:33 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_charjoin(char	*str, char c)
{
	char	*p;
	int		x;

	p = malloc(ft_strlen(str) + 2);
	x = -1;
	while(str[++x])
		p[x] = str[x];
	p[x++] = c;
	p[x] = 0;
	free(str);
	return (p);
}

char	*var_value(char	*str, char	**env)
{
	int	x;

	x = -1;
	while (env[++x])
	{
		if (!ft_strncmp(env[x], str, ft_strlen(str)) && env[x][ft_strlen(str)] == '=')
			return (env[x] + ft_strlen(str) + 1);
	}
	return (0);
}

char	*var_name(char	*str, int	*x)
{
	int		i;
	char	*p;

	i = 0;
	while(str[i] && str[i] != ' ' && str[i] != '\"')
		i++;
	p = malloc(i + 1);
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\"')
	{
		p[i] = str[i];
		i++;
		*x += 1;
	}
	p[i] = 0;
	return (p);
}

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
	char	*var;

	(void)type;
	buff = ft_calloc(ft_strlen(str) + 1, 1);
	i = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == '\"')
		{
			x++;
			while (str[x] && str[x] != '\"')
			{
				if (str[x] == '$')
				{
					x++;
					var = var_value(var_name(str + x, &x), env);
					if (var)
						buff = ft_strjoin(buff, var);
					i = ft_strlen(buff);
				}
				else
					buff[i++] = str[x++];
			}
		}
		else if (str[x] == '\'')
		{
			x++;
			while (str[x] && str[x] != '\'')
				buff[i++] = str[x++];
		}
		else
			buff[i++] = str[x++];
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
	// i = -1;
	// while (minish->options[++i])
	// 	printf("%s\n", minish->options[i]);
	return (minish->options);
}
