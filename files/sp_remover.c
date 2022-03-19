/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_remover.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 15:47:02 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/19 16:08:03 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*rm_late_sp(char	*s)
{
	int	lenght;

	lenght = ft_strlen(s);
	while (s[lenght - 1] == ' ')
	{
		s[lenght -1] = '\0';
		lenght--;
	}
	return (s);
}

char	*rm_early_sp(char	*s)
{
	while (s[0] == ' ')
		s++;
	return (s);
}
