/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 12:44:56 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/10 10:22:57 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	*ft_memset(void	*s, int c, size_t n)
{
	int		x;
	char	*ss;

	ss = s;
	x = 0;
	while (x < (int)n)
	{
		ss[x] = (unsigned char)c;
		x++;
	}
	return (ss);
}
