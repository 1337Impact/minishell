/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 21:25:27 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/20 05:22:51 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstdelone(t_list	*lst, void (*del)(void*))
{
	if (lst || del)
	{
		del(lst->content);
		free(lst);
		lst = NULL;
	}
}
