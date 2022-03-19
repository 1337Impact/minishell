/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:01:16 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/14 18:59:17 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strtrim(char const	*s, char const	*set)
{
	char	*p;
	size_t	x;
	size_t	slen;

	x = 0;
	if (s != 0 && set != 0)
	{
		slen = ft_strlen(s);
		while (s[x] && ft_memchr(set, s[x], ft_strlen(set)))
			x++;
		while (s[x] && ft_memchr(set, s[slen - 1], ft_strlen(set)))
			slen--;
		p = ft_substr(s, x, slen - x);
		return (p);
	}
	return (0);
}
