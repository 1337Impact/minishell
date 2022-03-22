/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:43:00 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/22 15:52:23 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	echo(char	**options)
{
	int	x;

	if (!ft_strncmp(options[1], "-n", 3))
		x = 1;
	else
		x = 0;
	while (options[++x])
	{
		ft_putstr_fd(options[x], 1);
		write(1, " ", 1);
	}
	ft_putstr_fd(options[x], 1);
	if (ft_strncmp(options[1], "-n", 3))
		write(1, "\n", 1);
}
