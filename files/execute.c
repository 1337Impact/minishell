/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenkhat <mbenkhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:04:25 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/26 18:08:21 by mbenkhat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(char *input, t_minishell *minishell, char **argv)
{
	if (!fork())
	{
		if (execve(input, argv, minishell->local_env) == -1)
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
