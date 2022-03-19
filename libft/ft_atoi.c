/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:18:02 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/14 12:51:40 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_atoi(const char	*s)
{
	size_t			x;
	int				sign;
	unsigned long	out;

	x = 0;
	sign = 1;
	out = 0;
	while (s[x] == 32 || s[x] == 10 || s[x] == 9
		|| s[x] == 11 || s[x] == 12 || s[x] == 13)
		x++;
	if (s[x] == '-' || s[x] == '+')
	{
		if (s[x] == '-')
			sign *= -1;
		x++;
	}
	while (s[x] >= '0' && s[x] <= '9')
		out = out * 10 + s[x++] - 48;
	if (out > 4294967295)
	{
		if (sign == -1)
			return (0);
		return (-1);
	}
	return (sign * out);
}
