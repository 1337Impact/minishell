/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 11:29:43 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/12 21:12:47 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memcpy(void	*dst, const void	*src, size_t n)
{
	int			x;
	const char	*s;
	char		*d;

	x = 0;
	s = src;
	d = dst;
	if (dst != 0 || src != 0)
	{
		while (x < (int)n)
		{
			d[x] = s[x];
			x++;
		}
	}
	return (dst);
}
