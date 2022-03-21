/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 15:29:23 by tnamir            #+#    #+#             */
/*   Updated: 2022/03/21 18:06:37 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmds(char *input)
{
	int i;
	int	counter;

	i = -1;
	counter = 0;
	while (input[++i])
	{
		if (input[i] == ' ')
			counter++;
		while (input[i] == ' ')
			i++;
		if (input[i] == '\'' || input[i] == '\"')
		{
			i++;
			while (input[i] != '\'' && input[i] != '\"')
				i++;
		}
	}
	return (++counter);
}

// static	int	cpy_till_char(char	*input, char c)
// {
// 	int	x;

// 	x = -1;
// 	while (input[++x] != c)
// 		;
// 	return (x);
// }

// static void	quote(char	*input, char	**options)
// {
// 	int	x;
// 	int	y;

// 	x = -1;
// 	y = 0;
// 	while (input[++x])
// 	{
// 		if (input[x] == '\'')
// 			;
// 		printf("%s\n", ft_substr(options[y], x, cpy_till_char(input, ' ')));
// 		y++;
// 	}
// 	return ;
// }

void	quotes_presence(char	*input, char **options)
{
	// char	*options[50];
	// int		i;

	// i = 0;
	// quote(input, options);
	(void)options;
	printf("%d\n", count_cmds(input));
	//return (options);
}