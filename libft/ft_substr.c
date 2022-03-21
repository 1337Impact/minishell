/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 12:27:52 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/21 20:09:04 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_substr(char	const	*s, unsigned int start, size_t len)
{
	char		*p;
	size_t		y;

	y = 0;
	if (s != 0)
	{
		if (ft_strlen(s) > len)
			p = malloc(len * sizeof(char) + 1);
		else
			p = malloc(ft_strlen(s) * sizeof(char) + 1);
		if (p == NULL || p == 0)
			return (0);
		while (start < ft_strlen(s) && len)
		{
			p[y] = s[start];
			start++;
			y++;
			len--;
		}
		p[y] = 0;
		return (p);
	}
	return (0);
}
