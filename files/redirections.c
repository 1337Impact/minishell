/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnamir <tnamir@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:52:37 by mbenkhat          #+#    #+#             */
/*   Updated: 2022/04/17 22:56:59 by tnamir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*redirect_output(t_minishell *minish, char *input, int x)
{
	char	*cmd;
	char	*file;

	cmd = ft_substr(input, 0, x);
	input += x + 1;
	file = who_file(input, minish);
	minish->w_fd = open(file, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if (minish->w_fd == -1)
	{
		print_error("minishell : no such file or directory:",
			file, minish, 1);
		return (0);
	}
	minish->p = 1;
	conditions(minish, cmd);
	close(minish->w_fd);
	x = check_metacharacters(input);
	free(file);
	if (!input[x])
	{
		free(cmd);
		return (0);
	}
	return (redirect_strjoin(cmd, input + x));
}

char	*redirect_input(t_minishell *minish, char *input, int x)
{
	char	*cmd;
	char	*file;

	cmd = ft_substr(input, 0, x);
	input += x + 1;
	file = who_file(input, minish);
	minish->r_fd = open(file, O_RDWR, S_IRWXU);
	if (minish->r_fd == -1)
	{
		ft_putstr_fd("minishell : ", 2);
		ft_putstr_fd(file, 2);
		ft_putendl_fd(": no such file or directory:", 2);
		return (0);
	}
	minish->p = 3;
	conditions(minish, cmd);
	close(minish->r_fd);
	free(file);
	x = check_metacharacters(input);
	if (!input[x])
	{
		free(cmd);
		return (0);
	}
	return (redirect_strjoin(cmd, input + x));
}

char	*redirect_append(t_minishell *minish, char *input, int x)
{
	char	*cmd;
	char	*file;

	cmd = ft_substr(input, 0, x);
	input += x + 2;
	file = who_file(input, minish);
	minish->w_fd = open(file, O_RDWR | O_APPEND | O_CREAT, S_IRWXU);
	if (minish->w_fd == -1)
	{
		print_error("minishell : no such file or directory:",
			file, minish, 1);
		return (0);
	}
	minish->p = 1;
	conditions(minish, cmd);
	close(minish->w_fd);
	free(file);
	x = check_metacharacters(input);
	if (!input[x])
	{
		free(cmd);
		return (0);
	}
	return (redirect_strjoin(cmd, input + x));
}

void	check_input(t_minishell *minish, char *delim)
{
	char	*rd_input;

	rd_input = NULL;
	rd_input = readline("heredoc> ");
	while (ft_strncmp(rd_input, delim, ft_strlen(delim) + 1) && rd_input)
	{
		ft_putendl_fd(rd_input, minish->w_fd);
		free(rd_input);
		rd_input = readline("heredoc> ");
	}
	free(rd_input);
}

char	*delimiter_input(t_minishell *minish, char *input, int x)
{
	char	*cmd;
	char	*delimiter;
	char	*rd_input;

	cmd = ft_substr(input, 0, x);
	input += x + 2;
	delimiter = who_file(input, minish);
	rd_input = NULL;
	minish->w_fd = open("/tmp/minishell", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	check_input(minish, delimiter);
	close(minish->w_fd);
	minish->p = 3;
	minish->r_fd = open("/tmp/minishell", O_RDWR, S_IRWXU);
	minish->w_fd = 1;
	conditions(minish, cmd);
	close(minish->r_fd);
	free(delimiter);
	x = check_metacharacters(input);
	if (!input[x])
	{
		free(cmd);
		return (0);
	}
	return (redirect_strjoin(cmd, input + x));
}
