/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:04:25 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/24 17:31:41 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(char *input, char **envp, t_minishell *minishell, char **argv)
{
	(void)minishell;
	if (!fork())
	{
		if (execve(input, argv, envp) == -1)
		{
			minishell->exit_status = errno;
			perror("error ");
		}
		else
			minishell->exit_status = 0;
	}
	else
		wait(NULL);
}
