/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 14:02:27 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/08 19:11:36 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_memcmp(const void	*s1, const void	*s2, size_t n)
{
	int			x;
	const char	*s11;
	const char	*s22;

	x = 0;
	s11 = s1;
	s22 = s2;
	while (x < (int)n)
	{
		if (s11[x] != s22[x])
			return ((unsigned char)s11[x] - (unsigned char)s22[x]);
		x++;
	}
	return (0);
}
