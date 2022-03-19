/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 22:10:58 by tnamir            #+#    #+#             */
/*   Updated: 2021/11/17 22:14:12 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (lst || new)
	{
		temp = *lst;
		if (*lst == NULL)
			*lst = new;
		else
		{
			while (temp->next != NULL)
				temp = temp->next;
			temp->next = new;
		}
	}
}
