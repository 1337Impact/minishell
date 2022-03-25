/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenkhat <mbenkhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 18:55:01 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/25 11:30:29 by mbenkhat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*before_equal(char *str)
{
	int		x;
	char	*p;

	x = 0;
	if (str)
	{
		while (str[x] && str[x] != '=')
			x++;
		x++;
		p = malloc(x);
		x = 0;
		while (str[x] && str[x] != '=')
		{
			p[x] = str[x];
			x++;
		}
		p[x] = '=';
		p[x + 1] = '\0';
		return (p);
	}
	return (0);
}

static char	*after_equal(char *str)
{
	int	size;
	int	x;

	size = ft_strlen(str);
	x = 0;
	while (str[x] && str[x] != '=')
		x++;
	x++;
	if (x == size)
		return ("\'\'");
	return (str + x);
}

void	export(t_minishell *minish, char *new_var)
{
	int		x;
	char	**tmp_env;
	char	*name;

	x = -1;
	if (new_var)
	{
		tmp_env = minish->new_env;
		minish->new_env
			= malloc((twod_array_len(minish->new_env) + 1) * sizeof(char *));
		while (tmp_env[++x])
			minish->new_env[x] = tmp_env[x];
		if (ft_strchr(new_var, '='))
		{
			name = before_equal(new_var);
			minish->new_env[x++] = ft_strjoin(name, after_equal(new_var));
			free(name);
		}
		else
			minish->new_env[x++] = ft_strjoin(new_var, "=\'\'");
		minish->new_env[x] = NULL;
		x = -1;
	}
	else
	{
		x = 0;
		while (minish->new_env[x++])
			ft_putendl_fd(minish->new_env[x], 1);
	}
}

