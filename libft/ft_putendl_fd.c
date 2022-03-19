/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 18:01:08 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/16 18:18:52 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	size_t	x;

	x = 0;
	if (s != 0)
	{
		while (s[x])
		{
			write(fd, &s[x], sizeof(char));
			x++;
		}
		write(fd, "\n", sizeof(char));
	}
}
