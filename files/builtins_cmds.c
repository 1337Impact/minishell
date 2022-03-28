/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cmds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenkhat <mbenkhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:43:00 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/28 10:05:12 by mbenkhat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	cd(char *path, t_minishell *minish)
{
	if (f_or_d(path) != 'd')
	{
		ft_putstr_fd("error: no such file or directory: ", 2);
		ft_putendl_fd(path, 2);
		minish->exit_status = 2;
		return ;
	}
	if (access(path, X_OK))
	{
		ft_putstr_fd("error: permission denied: ", 2);
		ft_putendl_fd(path, 2);
		minish->exit_status = 13;
		return ;
	}
	minish->exit_status = 0;
	chdir(path);
}

void	env(char	**env, t_minishell *minish)
{
	int	i;

	i = -1;
	if (!fork())
		while (env[++i])
			ft_putendl_fd(env[i], minish->w_fd);
	else
		wait(0);
	minish->exit_status = 0;
}
