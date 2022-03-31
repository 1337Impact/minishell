/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:52:37 by mbenkhat          #+#    #+#             */
/*   Updated: 2022/03/31 14:51:57 by tnamir           ###   ########.fr       */
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

char	*redirect_output(t_minishell *minish, char *input, int x)
{
	char	*cmd;
	char	*file_name;

	cmd = ft_substr(input, 0, x);
	input += x + 1;
	file_name = one_file_input(rm_late_sp(rm_early_sp(input)));
	file_name = quotes_handler(ft_substr(file_name, 0, check_metacharacters(file_name)), minish);
	minish->w_fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if (minish->w_fd == -1)
	{
		print_error("minishell : no such file or directory:", file_name, minish, 1);
		return (0);
	}
	minish->p = 1;
	conditions(minish, cmd);
	close(minish->w_fd);
	x = check_metacharacters(input);
	if (!input[x])
		return (0);
	return(ft_strjoin(cmd, input + x));
}

char	*redirect_input(t_minishell *minish, char *input, int x)
{
	char	*cmd;
	char	*file_name;

	cmd = ft_substr(input, 0, x);
	input += x + 1;
	file_name = one_file_input(rm_late_sp(rm_early_sp(input)));
	file_name = quotes_handler(ft_substr(file_name, 0, check_metacharacters(file_name)), minish);
	minish->r_fd = open(file_name, O_RDWR, S_IRWXU);
	if (minish->r_fd == -1)
	{
		print_error("minishell : no such file or directory:", file_name, minish, 1);
		return (0);
	}
	minish->p = 3;
	conditions(minish, cmd);
	close(minish->r_fd);
	x = check_metacharacters(input);
	if (!input[x])
		return (0);
	minish->p = 3;
	return(ft_strjoin(cmd, input + x));
}

char	*redirect_append(t_minishell *minish, char *input, int x)
{
	char	*cmd;
	char	*file_name;

	cmd = ft_substr(input, 0, x - 1);
	input += x + 2;
	file_name = one_file_input(rm_late_sp(rm_early_sp(input)));
	file_name = quotes_handler(ft_substr(file_name, 0, check_metacharacters(file_name)), minish);
	printf("%s", file_name);
	minish->w_fd = open(file_name, O_RDWR | O_APPEND | O_CREAT , S_IRWXU);
	if (minish->w_fd == -1)
	{
		print_error("minishell : no such file or directory:", file_name, minish, 1);
		return (0);
	}
	minish->p = 1;
	conditions(minish, cmd);
	close(minish->w_fd);
	x = check_metacharacters(input);
	if (!input[x])
		return (0);
	return(ft_strjoin(cmd, input + x));
}
void	delimiter_input()
{
	printf("delimiter_input\n");
}
void	parse_error()
{
	printf("parse_error\n");
}