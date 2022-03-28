/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:04:25 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/28 15:22:26 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(char *input, t_minishell *minish, char **argv)
{
	if (!fork())
	{
		if (minish->p)
		{
			if (minish->p == 1 || minish->p == 2)
				dup2(minish->w_fd, 1);
			if (minish->p == 3 || minish->p == 2)
				dup2(minish->r_fd, 0);
		}
		if (execve(input, argv, minish->local_env) == -1)
		{
			minish->exit_status = errno;
			perror("error ");
		}
		else
			minish->exit_status = 0;
	}
	else
		wait(NULL);
}
