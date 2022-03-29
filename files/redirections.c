/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:52:37 by mbenkhat          #+#    #+#             */
/*   Updated: 2022/03/29 16:24:29 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	redirecting_output(t_minishell *minish, char *input, int x)
{
	(void)input;
	(void)x;
	minish->w_fd = open(minish->options[x + 1], O_APPEND | O_RDWR | O_CREAT, S_IRWXU);
}

void	redirections(t_minishell *minish, int x)
{
	if (ft_strchr(minish->options[x], '>'))
	{
		minish->options[x] = NULL;
		redirecting_output(minish, minish->options[x], x);
	}
}

int	redirections_check(t_minishell *minish)
{
	int	x;

	x = -1;
	while (minish->options[++x])
	{
		if (ft_strchr(minish->options[x], '<') || ft_strnstr(minish->options[x], "<<", ft_strlen(minish->options[x]))
			|| ft_strchr(minish->options[x], '>') || ft_strnstr(minish->options[x], ">>", ft_strlen(minish->options[x])))
			redirections(minish, x);
	}
	return (0);
}
