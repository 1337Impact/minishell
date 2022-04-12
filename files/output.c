/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 15:38:43 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/11 16:18:25 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*output(t_minishell *minish, char *input, int x)
{
	(void)minish;
	(void)x;
	if (input[0] == '>')
	{
		input++;
		while (*input == ' ')
			input++;
		printf("%s\n", input);
		fflush(stdout);
	}
	return (0);
}
