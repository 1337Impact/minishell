/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:55:03 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/01 15:50:02 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_hand(t_minishell *minish, char	*input, int x)
{
	int		start;
	char	*str;
	int		fd[2];

	input = rm_early_sp(rm_late_sp(input));
	start = 0;
	if (pipe(fd) == -1)
		return (2);
	if (minish->p < 2)
		minish->p += 1;
	minish->w_fd = fd[1];
	str = ft_substr(input, 0, x);
	conditions(minish, str);
	close(minish->w_fd);
	minish->w_fd = 1;
	minish->r_fd = fd[0];
	return (1);
}
