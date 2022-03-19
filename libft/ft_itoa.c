/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 10:40:23 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/14 14:38:58 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static int	intsize(int x)
{
	int				y;
	unsigned int	xx;

	xx = x;
	y = 1;
	if (x < 0)
		xx = -x;
	while (xx > 9)
	{
		y++;
		xx = xx / 10;
	}
	return (y);
}

char	*ft_itoa(int n)
{
	int				size;
	char			*charint;
	unsigned int	nn;

	nn = n;
	size = intsize(n);
	if (n < 0)
	{
		nn = -n;
		size += 1;
	}
	charint = (char *)malloc(size * sizeof(char) + 1);
	if (charint == NULL)
		return (0);
	charint[size] = 0;
	while (size)
	{
		charint[size - 1] = nn % 10 + 48;
		nn /= 10;
		size--;
	}
	if (n < 0)
		charint[0] = '-';
	return (charint);
}
