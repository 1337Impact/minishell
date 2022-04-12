/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:43:00 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/11 16:53:42 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_minishell *minishell)
{
	int	x;

	minishell->exita = 1;
	x = -1;
	if (minishell->options[1])
	{
		while (ft_isdigit(minishell->options[1][++x]))
			;
		if (minishell->options[1][x])
			ft_putendl_fd("minishell: exit: numeric argument required", 2);
		else
			minishell->exit_status = ft_atoi(minishell->options[1]);
	}
	ft_putstr_fd(RED"exit 💀\033[0m", 1);
}

void	echo(char	**options, t_minishell *minish)
{
	int	x;

	if (options[0])
	{
		if (!ft_strncmp(options[1], "-n", 3))
			x = 1;
		else
			x = 0;
		while (options[++x])
		{
			ft_putstr_fd(options[x], minish->w_fd);
			write(1, " ", 1);
		}
		ft_putstr_fd(options[x], minish->w_fd);
	}
	if (ft_strncmp(options[1], "-n", 3))
		ft_putchar_fd('\n', minish->w_fd);
	minish->exit_status = 0;
}

static void	just_cd_error(char *path, t_minishell *minish)
{
	if (twod_array_len(minish->options) == 1)
	{
		path = var_value("HOME", minish->local_env);
		if (!path)
		{
			ft_putendl_fd("minishell: cd: HOME not set", 2);
			minish->exit_status = 1;
			return ;
		}
		chdir(path);
	}
	else
	{
		ft_putstr_fd("cd: string not in pwd: ", 2);
		ft_putendl_fd(path, 2);
		minish->exit_status = 1;
	}
	return ;
}

void	cd(char *path, t_minishell *minish)
{
	minish->exit_status = 0;
	if (twod_array_len(minish->options) == 1
		|| twod_array_len(minish->options) > 2)
		return (just_cd_error(path, minish));
	if (chdir(path) == -1)
	{
		perror("error");
		minish->exit_status = 1;
	}
}

void	env(char	**env, t_minishell *minish)
{
	int	i;

	(void)env;
	i = -1;
	while (minish->local_env[++i])
		ft_putendl_fd(minish->local_env[i], minish->w_fd);
	minish->exit_status = 0;
}
