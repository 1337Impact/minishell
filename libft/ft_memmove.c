/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 09:36:14 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/13 20:24:06 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memmove(void	*dst, const void	*src, size_t n)
{
	const char	*s;
	char		*d;
	size_t		indexer;

	s = src;
	d = dst;
	indexer = 0;
	if (dst != 0 || src != 0)
	{
		while (n > indexer)
		{
			if (d > s)
			{
				n--;
				d[n] = s[n];
			}
			else
			{
				d[indexer] = s[indexer];
				indexer++;
			}
		}
	}
	return (dst);
}
