/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenkhat <mbenkhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 11:29:51 by mbenkhat          #+#    #+#             */
/*   Updated: 2022/03/25 13:41:30 by mbenkhat         ###   ########.fr       */
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

char	**unset(char	**local_env, char *var)
{
	int		i;
	int		x;
	int		len;
	char	**new_env;

	if (!is_var(local_env, var))
		return (local_env);
	new_env = malloc(twod_array_len(local_env) * sizeof(char *));
	i = 0;
	x = 0;
	len = ft_strlen(var);
	while (local_env[i])
	{
		if (!ft_strncmp(local_env[i], var, len) && local_env[i][len] == '=')
			free(local_env[i]);
		else
			new_env[x] = local_env[i];
		i++;
		x++;
	}
	new_env[x] = 0;
	free(local_env);
	return	(new_env);
}

static char	*var_name_func(char *var)
{
	int	i;
	char	*var_name;

	i = 0;
	while (var[i] != '=')
		i++;
	var_name = malloc(i + 1);
	i = -1;
	while (var[++i] != '=')
		var_name[i] = var[i];
	return (var_name);
}

char	**export(char	**local_env, char *new_var)
{
	int		x;
	char	**new_env;
	char	*var_name;

	
	var_name = var_name_func(new_var);
	if (is_var(local_env, var_name))
		new_env = unset(local_env, var_name);
	new_env = malloc((twod_array_len(local_env) + 2) * sizeof(char *));
	x = 0;
	while (local_env[x])
	{
		new_env[x] = local_env[x];
		x++;
	}
	new_env[x] = ft_strdup(new_var);
	x++;
	new_env[x] = 0;
	free(local_env);
	// free(var_name);
	return (new_env);
}
