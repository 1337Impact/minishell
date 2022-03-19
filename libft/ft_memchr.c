/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 13:29:07 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/12 21:42:05 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memchr(const void	*s, int c, size_t n)
{
	size_t			x;
	const char		*ss;

	x = 0;
	ss = s;
	while (x < n)
	{
		if ((unsigned char)ss[x] == (unsigned char)c)
			return ((void *)&ss[x]);
		x++;
	}
	return (NULL);
}
