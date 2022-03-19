/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:51:33 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/19 16:02:53 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*newlist;

	if (lst || f || del)
	{
		list = NULL;
		while (lst)
		{
			newlist = ft_lstnew(f(lst->content));
			if (newlist == NULL)
			{
				ft_lstclear(&list, del);
				return (0);
			}
			ft_lstadd_back(&list, newlist);
			lst = lst->next;
		}
		return (list);
	}
	return (0);
}
