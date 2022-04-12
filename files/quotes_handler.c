/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:29:23 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/09 08:01:33 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_charjoin(char	*str, char c)
{
	char	*p;
	int		x;

	p = malloc(ft_strlen(str) + 2);
	x = -1;
	while (str[++x])
		p[x] = str[x];
	p[x++] = c;
	p[x] = 0;
	free(str);
	return (p);
}

char	*double_quotes_handl(char *str, t_minishell *minish, char *buff, int *x)
{
	*x += 1;
	while (str[*x] && str[*x] != '\"')
	{
		if (str[*x] == '$')
			buff = var_handler(buff, str, minish, x);
		else
		{
			buff = ft_charjoin(buff, str[*x]);
			*x += 1;
		}
	}
	*x += 1;
	return (buff);
}

char	*quotes_handler(char *str, t_minishell *minish)
{
	char	*buff;
	int		x;

	buff = ft_calloc(ft_strlen(str) + 1, 1);
	x = 0;
	while (str[x])
	{
		if (str[x] == '$')
			buff = var_handler(buff, str, minish, &x);
		else if (str[x] == '\'')
		{
			x++;
			while (str[x] && str[x] != '\'')
				buff = ft_charjoin(buff, str[x++]);
			x++;
		}
		else if (str[x] == '\"')
			buff = double_quotes_handl(str, minish, buff, &x);
		else
			buff = ft_charjoin(buff, str[x++]);
	}
	return (buff);
}

char	**quotes_presence(char	*input, t_minishell	*minish)
{
	int		i;
	char	*str;

	i = -1;
	minish->options = cpy_it(input, minish->options);
	while (minish->options[++i])
	{
		str = minish->options[i];
		minish->options[i] = quotes_handler(minish->options[i], minish);
		free(str);
	}
	return (minish->options);
}
