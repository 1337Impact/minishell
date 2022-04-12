/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metacharacters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 08:57:42 by mbenkhat          #+#    #+#             */
/*   Updated: 2022/04/12 18:00:45 by tnamir           ###   ########.fr       */
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

///// while x + 1 to increment input after to let it pass spaces

void	pipex(char *input, t_minishell *minish, int *x)
{
	pipe_hand(minish, input, *x);
	while (input[*x + 1] == ' ')
		*x += 1;
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
			print_error("minishell: parse error", NULL, minish, 130);
		else if (input[x] == '>')
		{
			if (input[x] == '>' && input[x - 1] == '>')
				input = redirect_append(minish, input, x);
			else
				input = redirect_output(minish, input, x);
			if (!input)
				return (1);
			x = -1;
		}
		else if (input[x] == '<')
		{
			if (input[x] == '<' && input[x - 1] == '<')
				input = delimiter_input(minish, input, x);
			else
				input = redirect_input(minish, input, x);
			if (!input)
				return (1);
			x = -1;
		}
		else if (input[x] == '|')
			pipex(input, minish, &x);
		input += x + 1;
	}
	return (1);
}
