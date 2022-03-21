/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:04:25 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/19 18:18:27 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute(char *input, char **envp, t_minishell *minishell, char **argv)
{
	(void)minishell;
	if (!fork())
	{
		if (execve(input, argv, envp) == -1) 
			perror("error ");
	}
	else
		wait(NULL);
}
