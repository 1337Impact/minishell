/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metacharacters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 08:57:42 by mbenkhat          #+#    #+#             */
/*   Updated: 2022/03/31 13:23:16 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_metacharacters(char *input)
{
	int	i;

	i = -1;
	while (input[++i])
	{
		if (input[i] == '\"')
		{
			i++;
			while (input[i] != '\"' && input[i])
				i++;
		}
		else if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'' && input[i])
				i++;
		}
		else if (input[i] == '>' || input[i] == '<' || input[i] == '|')
			break ;
		if (!input[i])
			break ;
	}
	return (i);
}

int	check_metacharacters(char *input)
{
	int	i;

	i = get_metacharacters(input);
	if (!input[i])
		return (i);
	if (input[i] == '>')
	{
		if (input[i + 1] == '>')
			i++;
	}
	else if (input[i] == '<')
	{
		if (input[i + 1] == '<')
			i++;
	}
	if (!(ft_isalnum(input[i + 1]) || input[i + 1] == '\''
			|| input[i + 1] == '\"' || input[i + 1] == '$'
			|| input[i + 1] == ' '))
		return (0);
	return (i);
}

int	metacharacters(char *input, t_minishell *minish)
{
	int		x;

	(void)minish;
	x = check_metacharacters(input);
	if (!input[x])
		return (0);
	x = 1;
	while (x)
	{
		x = check_metacharacters(input);
		if (!input[x])
		{
			minish->p = 3;
			conditions(minish, input);
			close(minish->r_fd);
			return (1);
		}
		if (!x)
			parse_error();
		else if (input[x] == '>' && input[x - 1] == '>')
			redirect_append();
		else if (input[x] == '<' && input[x - 1] == '<')
			delimiter_input();
		else if (input[x] == '>')
		{
			input = redirect_output(minish, input, x);
			if (!input)
				return (1);
			x = -1;
		}
		else if (input[x] == '<')
		{
			input = redirect_input(minish, input, x);
			if (!input)
				return (1);
			x = -1;
		}
		else if (input[x] == '|')
		{
			pipe_hand(minish, input, x);
		}
		input += x + 1;
	}
	return (1);
}
