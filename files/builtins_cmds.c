/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:43:00 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/23 18:38:05 by tnamir           ###   ########.fr       */
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
			ft_putstr_fd(options[x], 1);
			write(1, " ", 1);
		}
		ft_putstr_fd(options[x], 1);
	}
	if (ft_strncmp(options[1], "-n", 3))
		write(1, "\n", 1);
	minish->exit_status = 0;
}

void	cd(char *path, t_minishell *minish)
{
	if (f_or_d(path) != 'd')
	{
		printf("error: no such file or directory: %s\n", path);
		minish->exit_status = 2;
		return ;
	}
	if (access(path, X_OK))
	{
		printf("error: permission denied: %s\n", path);
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
	while (env[++i])
		ft_putendl_fd(env[i], 1);
	minish->exit_status = 0;
}
