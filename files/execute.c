/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:04:25 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/17 16:33:23 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*check_access(char *cmd, char **all_paths)
{
	int		x;
	char	*cmd_path;
	char	*path;

	x = -1;
	while (all_paths[++x])
	{
		path = ft_strjoin(all_paths[x], "/");
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		if (!access(cmd_path, F_OK) && !access(cmd_path, X_OK))
		{
			twod_free(all_paths);
			free(cmd);
			return (cmd_path);
		}
		free(cmd_path);
	}
	free(cmd);
	twod_free(all_paths);
	return (0);
}

static char	*valid_cmd(t_minishell *minish, char	*cmd)
{
	char	**all_paths;
	int		x;

	if (minish->local_env[0])
	{
		x = 0;
		while (ft_strncmp(minish->local_env[x], "PATH=", 5)
			&& minish->local_env[x])
			x++;
		if (minish->local_env[x])
		{
			all_paths = ft_split(minish->local_env[x] + 5, ':');
			return (check_access(cmd, all_paths));
		}
	}
	return (0);
}

void	errory(t_minishell *minish)
{
	minish->exit_status = 127;
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putendl_fd(minish->options[0], 2);
	return ;
}

static void	fd_hand(t_minishell *minish)
{
	if (minish->p == 1 || minish->p == 2)
	{
		dup2(minish->w_fd, 1);
		close(minish->w_fd);
	}
	if (minish->p == 3 || minish->p == 2)
	{
		dup2(minish->r_fd, 0);
		close(minish->r_fd);
	}
}

void	execute(char *cmd, t_minishell *minish, char **argv)
{
	int	status;

	minish->exit_status = 0;
	if (cmd[0] != '/' && cmd[0] != '.')
		cmd = valid_cmd(minish, cmd);
	if (!cmd || cmd[0] == '\0')
		return (errory(minish));
	if (!fork())
	{
		if (minish->p)
			fd_hand(minish);
		if (execve(cmd, argv, minish->local_env) == -1)
		{
			perror("minishell: error ");
			exit(127);
		}
	}
	else
	{
		wait(&status);
		minish->exit_status = WEXITSTATUS(status);
		free(cmd);
	}
}
