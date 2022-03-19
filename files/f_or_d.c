/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_or_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 20:19:24 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/18 13:18:54 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	f_or_d(char *input)
{
	struct stat	st;

	if (stat(input, &st) != -1)
	{
		if (S_ISREG(st.st_mode))
			return ('f');
		else if (S_ISDIR(st.st_mode))
			return ('d');
	}
	return (0);
}
