/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenkhat <mbenkhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:52:37 by mbenkhat          #+#    #+#             */
/*   Updated: 2022/03/30 10:44:27 by mbenkhat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// static void	redirecting_output(t_minishell *minish, char *input, int x)
// {
// 	(void)input;
// 	(void)x;
// 	minish->w_fd = open(minish->options[x + 1], O_APPEND | O_RDWR | O_CREAT, S_IRWXU);
// }

// void	redirections(t_minishell *minish, int x)
// {
// 	if (ft_strchr(minish->options[x], '>'))
// 	{
// 		minish->options[x] = NULL;
// 		redirecting_output(minish, minish->options[x], x);
// 	}
// }

// int	redirections_check(t_minishell *minish)
// {
// 	int	x;

// 	x = -1;
// 	while (minish->options[++x])
// 	{
// 		if (ft_strchr(minish->options[x], '<') || ft_strnstr(minish->options[x], "<<", ft_strlen(minish->options[x]))
// 			|| ft_strchr(minish->options[x], '>') || ft_strnstr(minish->options[x], ">>", ft_strlen(minish->options[x])))
// 			redirections(minish, x);
// 	}
// 	return (0);
// }

void	redirect_output()
{
	printf("redirect_output\n");
}
void	redirect_append()
{
	printf("redirect_append\n");
}
void	delimiter_input()
{
	printf("delimiter_input\n");
}
void	redirect_input()
{
	printf("redirect_input\n");
}
void	parce_error()
{
	printf("parce_error\n");
}