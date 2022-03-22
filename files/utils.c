/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 16:41:40 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/22 17:47:24 by tnamir           ###   ########.fr       */
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

char	*buff_value_changer(char *buff)
{
	int	size;

	size = ft_strlen(buff);
	if (buff[ft_strlen(buff) - 1] == '\"')
		buff[ft_strlen(buff) - 1] = 0;
	size = -1;
	while (buff[++size] != '$')
		size++;
	return (buff);
}