/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenkhat <mbenkhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 12:55:03 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/30 15:12:05 by mbenkhat         ###   ########.fr       */
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
	str = ft_substr(input, 0, x - 1);
	conditions(minish, str);
	close(minish->w_fd);
	minish->w_fd = 1;
	minish->r_fd = fd[0];
	return (1);
}