/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:41:40 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/29 16:41:49 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmds(char *input)
{
	int	i;
	int	counter;

	i = -1;
	counter = 0;
	while (input[++i])
	{
		if (input[i] == ' ')
			counter++;
		while (input[i] == ' ')
			i++;
		if (input[i] == '\'' || input[i] == '\"')
		{
			i++;
			while ((input[i] != '\'' && input[i] != '\"') && input[i])
				i++;
		}
	}
	return (++counter);
}

void	twod_free(char	**array)
{
	int	x;

	x = -1;
	while (array[++x])
		free(array[x]);
	free(array);
}
