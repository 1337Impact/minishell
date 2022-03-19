/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:41:25 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/13 19:37:22 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strnstr(const char *word, const char	*lookfor, size_t n)
{
	size_t	x;
	size_t	nn;

	nn = 0;
	x = 0;
	if (lookfor[0] == 0)
		return ((char *)word);
	while (word[x] && nn + x < n)
	{
		while (word[x] == lookfor[x] && nn + x < n)
		{
			x++;
			if (lookfor[x] == 0)
				return ((char *)word);
		}
		nn++;
		word++;
		x = 0;
	}
	return (0);
}
