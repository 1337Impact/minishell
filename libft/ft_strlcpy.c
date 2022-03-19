/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:06:00 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/11 21:06:30 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcpy(char	*dest, const char	*src, size_t dstlen)
{
	size_t	x;
	size_t	srcsize;

	x = 0;
	srcsize = ft_strlen(src);
	if (dstlen > 0)
	{
		while (src[x] && x < dstlen - 1 && dstlen > 1)
		{
			dest[x] = src[x];
			x++;
		}
		dest[x] = 0;
	}
	return (srcsize);
}
