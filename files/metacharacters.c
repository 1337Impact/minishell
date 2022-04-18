/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metacharacters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 08:57:42 by mbenkhat          #+#    #+#             */
/*   Updated: 2022/04/17 23:09:42 by tnamir           ###   ########.fr       */
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
	if (!(ft_isalnum(input[i + 1]) || input[i + 1] == '\''
			|| input[i + 1] == '\"' || input[i + 1] == '$'
			|| input[i + 1] == ' '
			|| (input[i + 1] == '>' && input[i + 2] != '>')
			|| (input[i + 1] == '<' && input[i + 2] != '<')))
		return (0);
	return (i);
}

void	pipex(char *input, t_minishell *minish, int *x)
{
	pipe_hand(minish, input, *x);
	while (input[*x + 1] == ' ')
		*x += 1;
}

char	*metacond(char *input, t_minishell *minish, int *x)
{
	if (*x == 0)
		print_error("minishell: parse error", NULL, minish, 130);
	else if (input[*x] == '>')
	{
		if (input[*x] == '>' && input[*x + 1] == '>')
			input = redirect_append(minish, input, *x);
		else
			input = redirect_output(minish, input, *x);
		if (!input)
			return (0);
		*x = -1;
	}
	else if (input[*x] == '<')
	{
		if (input[*x] == '<' && input[*x + 1] == '<')
			input = delimiter_input(minish, input, *x);
		else
			input = redirect_input(minish, input, *x);
		if (!input)
			return (0);
		*x = -1;
	}
	else if (input[*x] == '|')
		pipex(input, minish, x);
	return (input);
}

int	metacharacters(char *input, t_minishell *minish)
{
	int		x;

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
		else
		{
			input = metacond(input, minish, &x);
			if (!input)
				return (1);
		}
		input += x + 1;
	}
	return (1);
}
