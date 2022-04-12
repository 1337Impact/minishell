/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:29:51 by mbenkhat          #+#    #+#             */
/*   Updated: 2022/04/12 14:19:39 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_var(char	**local_env, char *var)
{
	int		i;
	char	*name;

	i = -1;
	while (local_env[++i])
	{
		name = var_name_func(local_env[i]);
		if (!ft_strncmp(local_env[i], var, ft_strlen(name)))
		{
			free(name);
			return (1);
		}
		free(name);
	}
	return (0);
}

char	**unset_var(char *var_name, char **local_env)
{
	int		i;
	int		x;
	int		len;
	char	**new_env;

	new_env = ft_calloc((twod_array_len(local_env) + 1), sizeof(char *));
	i = 0;
	x = 0;
	len = ft_strlen(var_name);
	while (local_env[i])
	{
		if (!ft_strncmp(local_env[i], var_name, len))
		{
			free(local_env[i]);
			i++;
			continue ;
		}
		new_env[x] = local_env[i];
		i++;
		x++;
	}
	new_env[x] = 0;
	free(local_env);
	return (new_env);
}

static int	valid_var_name(char	*var, t_minishell *minish)
{
	int	x;

	x = -1;
	while (var[++x])
	{
		if (!ft_isalnum(var[x]) || var[x] == '_')
		{
			ft_putstr_fd("unset: ", 2);
			ft_putstr_fd(var, 2);
			ft_putendl_fd(": invalid parameter name", 2);
			minish->exit_status = 1;
			return (1);
		}
	}
	return (0);
}

char	**unset(char **local_env, t_minishell *minish)
{
	int		y;

	minish->exit_status = 0;
	if (twod_array_len(minish->options) == 1)
	{
		ft_putendl_fd("unset: not enough arguments", 2);
		minish->exit_status = 1;
		return (local_env);
	}
	y = 0;
	while (minish->options[++y])
	{
		if (valid_var_name(minish->options[y], minish))
			continue ;
		if (!is_var(local_env, minish->options[y]))
			continue ;
		local_env = unset_var(minish->options[y], local_env);
	}
	return (local_env);
}
