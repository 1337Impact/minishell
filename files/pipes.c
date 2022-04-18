/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:55:03 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/18 21:53:07 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pipe_hand(t_minishell *minish, char	*input, int x)
{
	char	*str;
	int		fd[2];

	input = rm_early_sp(rm_late_sp(input));
	if (pipe(fd) == -1)
		return (2);
	if (minish->p < 2)
		minish->p += 1;
	minish->w_fd = fd[1];
	str = ft_substr(input, 0, x);
	conditions(minish, rm_early_sp(rm_late_sp(str)));
	close(minish->w_fd);
	minish->w_fd = 1;
	minish->r_fd = fd[0];
	free(str);
	return (1);
}
