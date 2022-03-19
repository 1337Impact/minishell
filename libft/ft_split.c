/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:40:15 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/23 14:40:19 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static char	**freee(char **p, int px)
{
	while (px)
	{
		free(p[px]);
		px--;
	}
	free(p);
	return (0);
}

static	size_t	charsearch(const char *s, int c)
{
	size_t	x;
	size_t	wordsnbr;

	x = 0;
	wordsnbr = 0;
	while (s[x])
	{
		while (s[x] == c && s[x])
			x++;
		if (s[x])
			wordsnbr++;
		while (s[x] != c && s[x])
			x++;
	}
	return (wordsnbr);
}

static char	**allocation(char const *s, char c)
{
	size_t	x;
	size_t	px;
	size_t	y;
	char	**p;

	px = 0;
	x = 0;
	y = 0;
	p = (char **)malloc(charsearch(s, c) * sizeof(char *) + 1);
	if (!p)
		return (0);
	while (px < charsearch(s, c))
	{
		while (s[y] == c)
			y++;
		x = y;
		while (s[x] != c && s[x])
			x++;
		p[px++] = ft_substr(s, y, x - y);
		if (p[px - 1] == NULL)
			return (freee(p, px));
		y = x;
	}
	p[px] = 0;
	return (p);
}

char	**ft_split(char const *s, char c)
{
	char	**p;

	if (!s)
		return (NULL);
	p = allocation(s, c);
	return (p);
}
