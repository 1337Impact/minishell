/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:15:18 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/19 17:01:58 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char	*s, int c)
{
	char		*ptr;
	size_t		j;

	ptr = NULL;
	j = 0;
	while (j <= ft_strlen(s))
	{
		if (s[j] == (char)c)
			ptr = (char *)&s[j];
		j++;
	}
	return (ptr);
}
