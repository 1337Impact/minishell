/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metacharacters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbenkhat <mbenkhat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 08:57:42 by mbenkhat          #+#    #+#             */
/*   Updated: 2022/03/30 13:52:46 by mbenkhat         ###   ########.fr       */
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
	if (!(ft_isalnum(input[i + 1]) || input[i + 1] == '\'' || input[i + 1] == '\"' || input[i + 1] == '$' || input[i + 1] == ' '))
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
			conditions(minish, rm_early_sp(rm_late_sp(input)));
			close(minish->r_fd);
			return (1);
		}
		else if (!x)
			parce_error();
		else if (input[x] == '>' && input[x - 1] == '>')
			redirect_append();
		else if (input[x] == '<' && input[x - 1] == '<')
			delimiter_input();
		else if (input[x] == '>')
			redirect_output();
		else if (input[x] == '<')
			redirect_input();
		else if (input[x] == '|')
			pipe_hand(minish, input, x);
		input += x + 1;
	}
	return (1);
}