/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenkhat <mbenkhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:04:25 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/29 10:51:43 by mbenkhat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

char	*valid_cmd(t_minishell *minish, char	*cmd)
{
	char	**all_paths;
	int		x;
	char	*path;
	char	*cmd_path;

	(void)cmd;
	x = 0;
	while (ft_strncmp(minish->local_env[x], "PATH=", 5))
		x++;
	all_paths = ft_split(minish->local_env[x] + 5, ':');
	x = -1;
	while (all_paths[++x])
	{
		path = ft_strjoin(all_paths[x], "/");
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		if (!access(cmd_path, F_OK))
		{
			twod_free(all_paths);
			return (cmd_path);
		}
		free(cmd_path);
	}
	twod_free(all_paths);
	return (0);
}

void	errory(t_minishell *minish)
{
	minish->exit_status = 127;
	printf("minishell: command not found: %s\n", minish->options[0]);
	return ;
}

void	execute(char *cmd, t_minishell *minish, char **argv)
{
	minish->exit_status = 0;
	if (cmd[0] != '/')
		cmd = valid_cmd(minish, cmd);
	if (!cmd)
		return (errory(minish));
	if (!fork())
	{
		if (minish->p)
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
				dup2(minish->w_fd, 1); // close(minish->w_fd);
			if (minish->p == 3 || minish->p == 2)
				dup2(minish->r_fd, 0); // close(minish->r_fd);
		}
		if (execve(cmd, argv, minish->local_env) == -1)
		{
			minish->exit_status = errno;
			perror("error ");
		}
	}
	else
		wait(NULL);
}
