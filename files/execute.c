/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenkhat <mbenkhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:04:25 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/28 15:46:47 by mbenkhat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(char *input, t_minishell *minish, char **argv)
{
	minish->exit_status = 0;
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
		}
		if (execve(input, argv, minish->local_env) == -1)
		{
			minish->exit_status = errno;
			perror("error ");
		}
	}
	else
		wait(NULL);
}
