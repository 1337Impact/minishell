/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:33:54 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/12 17:55:25 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char	*dest, const char	*src, size_t dstsize)
{
	size_t	srclen;
	size_t	dstlen;
	size_t	srcx;
	size_t	fakedstlen;

	srcx = 0;
	srclen = ft_strlen(src);
	dstlen = ft_strlen(dest);
	fakedstlen = ft_strlen(dest);
	if (dstsize > dstlen)
	{
		while (src[srcx] && dstsize - 1 > dstlen)
		{
			dest[dstlen] = src[srcx];
			srcx++;
			dstlen++;
		}
		dest[dstlen] = 0;
		return (srclen + fakedstlen);
	}
	else
		return (srclen + dstsize);
}
