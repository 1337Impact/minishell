/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:18:08 by tnamir            #+#    #+#             */
/*   Updated: 2022/04/16 17:54:12 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*one_file_input(char	*input)
{
	int	x;

	x = 0;
	while (input[x] != ' ' && input[x])
	{
		if (input[x] == '\'')
		{
			x++;
			while (input[x] != '\'')
				x++;
		}
		else if (input[x] == '\"')
		{
			x++;
			while (input[x] != '\"')
				x++;
		}
		x++;
	}
	return (ft_substr(input, 0, x));
}

char	*who_file(char *input, t_minishell *minish)
{
	char	*file_name;
	char	*file;
	char	*pure_file_name;

	file = one_file_input(rm_late_sp(rm_early_sp(input)));
	file_name = ft_substr(file, 0, check_metacharacters(file));
	free(file);
	pure_file_name = quotes_handler(file_name, minish);
	free(file_name);
	return (pure_file_name);
}
