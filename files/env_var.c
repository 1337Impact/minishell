/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:57:23 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/23 18:37:32 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*var_value(char	*str, char	**env)
{
	int	x;

	x = -1;
	while (env[++x])
	{
		if (!ft_strncmp(env[x], str, ft_strlen(str))
			&& env[x][ft_strlen(str)] == '=')
			return (env[x] + ft_strlen(str) + 1);
	}
	return (0);
}

static char	*var_name(char	*str, int	*x)
{
	int		i;
	char	*p;

	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\"'
		&& str[i] != '$' && str[i] != '/')
		i++;
	p = malloc(i + 1);
	i = 0;
	while (str[i] && str[i] != ' ' && str[i] != '\"'
		&& str[i] != '$' && str[i] != '/')
	{
		p[i] = str[i];
		i++;
		*x += 1;
	}
	p[i] = 0;
	return (p);
}

char	*var_handler(char *buff, char *str, t_minishell *minish, int *x)
{
	char	*var;

	*x += 1;
	if (str[*x] == '?')
	{
		buff = ft_strjoin(buff, ft_itoa(minish->exit_status));
		*x += 1;
	}
	else
	{
		var = var_value(var_name(str + *x, x), minish->env);
		if (var)
			buff = ft_strjoin(buff, var);
	}
	return (buff);
}

void	env_print(char	**env)
{
	int	i;

	i = -1;
	while (env[++i])
		ft_putendl_fd(env[i], 1);
}
