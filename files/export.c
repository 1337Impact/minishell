/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:05:27 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/16 23:37:56 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*var_name_func(char *var)
{
	int		i;
	char	*var_name;

	i = 0;
	while (var[i] != '=' && var[i])
		i++;
	var_name = malloc(i + 1);
	if (!var_name)
		return (0);
	i = -1;
	while (var[++i] != '=' && var[i])
		var_name[i] = var[i];
	var_name[i] = 0;
	return (var_name);
}

static int	valid_var_name(char	*var, t_minishell *minish)
{
	int		x;
	char	*name;

	x = -1;
	if (!var[0])
	{
		ft_putstr_fd("export: not valid in this context: ", 2);
		ft_putendl_fd(var, 2);
		minish->exit_status = 1;
		return (1);
	}
	name = var_name_func(var);
	while (name[++x])
	{
		if (!ft_isalnum(name[x]) && name[x] != '_' && name[x] != '=')
		{
			ft_putstr_fd("export: not valid in this context: ", 2);
			ft_putendl_fd(name, 2);
			minish->exit_status = 1;
			free(name);
			return (1);
		}
	}
	free(name);
	return (0);
}

static char	**export_check(t_minishell *minish, char **local_env, int y)
{
	int		i;
	char	*var_name;
	char	*name;

	var_name = var_name_func(minish->options[y]);
	if (is_var(local_env, var_name))
	{
		if (!ft_strchr(minish->options[y], '='))
		{
			i = 0;
			name = var_name_func(local_env[i]);
			while (local_env[i] && ft_strncmp(local_env[i], var_name \
			, ft_strlen(name)))
			{
				free(name);
				i++;
				name = var_name_func(local_env[i]);
			}
			free(name);
			minish->options[y] = ft_strdup(local_env[i]);
		}
		local_env = unset_var(var_name, local_env);
	}
	free(var_name);
	return (local_env);
}

char	**local_to_new(t_minishell *minish, char **local_env,
	int y, char **new_env)
{
	int		x;

	x = -1;
	while (local_env[++x])
		new_env[x] = local_env[x];
	new_env[x] = ft_strdup(minish->options[y]);
	new_env[++x] = 0;
	free(local_env);
	return (new_env);
}

char	**export(char	**local_env, t_minishell *minish)
{
	int		y;
	char	**new_env;

	minish->exit_status = 0;
	if (twod_array_len(minish->options) == 1)
		print_export(minish);
	if (twod_array_len(minish->options) > 1)
	{
		y = 0;
		while (minish->options[++y])
		{
			local_env = export_check(minish, local_env, y);
			if (valid_var_name(minish->options[y], minish))
				continue ;
			new_env = malloc((twod_array_len(local_env) + 2) * sizeof(char *));
			if (!new_env)
				return (0);
			local_env = local_to_new(minish, local_env, y, new_env);
		}
	}
	return (local_env);
}
