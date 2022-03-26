/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenkhat <mbenkhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:29:51 by mbenkhat          #+#    #+#             */
/*   Updated: 2022/03/25 18:26:25 by mbenkhat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_var(char	**local_env, char *var)
{
	int	i;
	int	len;

	len = ft_strlen(var);
	i = -1;
	while (local_env[++i])
	{
		if (!ft_strncmp(local_env[i], var, len) && local_env[i][len] == '=')
			return (1);
	}
	return (0);
}

static char	*var_name_func(char *var)
{
	int	i;
	char	*var_name;

	i = 0;
	while (var[i] != '=' && var[i])
		i++;
	var_name = malloc(i + 1);
	i = -1;
	while (var[++i] != '=' && var[i])
		var_name[i] = var[i];
	var_name[i] = 0;
	return (var_name);
}

char	**unset(char **local_env, t_minishell *minish)
{
	int		i;
	int		x;
	int		y;
	int		len;
	char	**new_env;
	char	*var_name;

	minish->exit_status = 0;
	if (twod_array_len(minish->options) == 1)
	{
		printf("unset: not enough arguments\n");
		minish->exit_status = 1;
		return (local_env);
	}
	y = 1;
	while (minish->options[y])
	{
		var_name = var_name_func(minish->options[y]);
		if (!is_var(local_env, var_name))
			continue ;
		new_env = malloc(twod_array_len(local_env) * sizeof(char *));
		i = 0;
		x = 0;
		len = ft_strlen(var_name);
		while (local_env[i])
		{
			if (!ft_strncmp(local_env[i], var_name, len) && local_env[i][len] == '=')
				free(local_env[i++]);
			new_env[x] = local_env[i];
			i++;
			x++;
		}
		new_env[x] = 0;
		free(local_env);
		local_env = new_env;
		y++;
	}
	return	(local_env);
}

char	**export(char	**local_env, t_minishell *minish)
{
	int		x;
	int		y;
	char	**new_env;
	char	*var_name;

	minish->exit_status = 0;
	if (twod_array_len(minish->options) == 1)
		env(local_env, minish);
	// else
	// 	local_env = unset(local_env, minish);
	y = 0;
	while (minish->options[++y])
	{
		if (!ft_strchr(minish->options[y], '='))
			continue ;
		var_name = var_name_func(minish->options[y]);
		new_env = malloc((twod_array_len(local_env) + 2) * sizeof(char *));
		x = 0;
		while (local_env[x])
		{
			new_env[x] = local_env[x];
			x++;
		}
		new_env[x] = ft_strdup(minish->options[y]);
		x++;
		new_env[x] = 0;
		free(local_env);
		local_env = new_env;
	}
	// free(var_name);
	return (local_env);
}
