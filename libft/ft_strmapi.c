/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:01:16 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/16 16:11:07 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*p;
	size_t	x;

	x = 0;
	if (s != 0)
	{
		p = malloc(ft_strlen(s) * sizeof(char) + 1);
		if (p == NULL)
			return (0);
		while (s[x])
		{
			p[x] = f(x, s[x]);
			x++;
		}
		p[x] = 0;
		return (p);
	}
	return (0);
}
