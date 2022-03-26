/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:05:27 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/26 12:44:15 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*var_name_func(char *var)
{
	int		i;
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

static int	valid_var_name(char	*var, t_minishell *minish)
{
	int	x;

	x = -1;
	while (var[++x])
	{
		if (!ft_isalnum(var[x]) && var[x] != '_' && var[x] != '=')
		{
			printf("export: not valid in this context: %s\n", var);
			minish->exit_status = 1;
			return (1);
		}
	}
	return (0);
}

static char	**export_check(t_minishell *minish, char **local_env)
{
	int		y;
	char	*var_name;

	y = 0;
	if (twod_array_len(minish->options) == 1)
		env(local_env, minish);
	else
	{
		while (minish->options[y])
		{
			var_name = var_name_func(minish->options[y]);
			if (is_var(local_env, var_name))
				local_env = unset_var(var_name, local_env);
			else
				y++;
			free(var_name);
		}
	}
	return (local_env);
}

char	**export(char	**local_env, t_minishell *minish)
{
	int		x;
	int		y;
	char	**new_env;

	minish->exit_status = 0;
	y = 0;
	local_env = export_check(minish, local_env);
	while (minish->options[++y])
	{
		if (valid_var_name(minish->options[y], minish)
			|| !ft_strchr(minish->options[y], '='))
			continue ;
		new_env = malloc((twod_array_len(local_env) + 2) * sizeof(char *));
		x = -1;
		while (local_env[++x])
			new_env[x] = local_env[x];
		new_env[x] = ft_strdup(minish->options[y]);
		x++;
		new_env[x] = 0;
		free(local_env);
		local_env = new_env;
	}
	return (local_env);
}
