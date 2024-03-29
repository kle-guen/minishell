/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:57:05 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/01 12:01:39 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

char	*error_msg(const char *filename)
{
	char	*error_msg;

	error_msg = ft_strjoin("msh: ", filename);
	g_exit_status = 1;
	return (error_msg);
}

void	print_redirection_error(const char *filename)
{
	char	*file_error;

	file_error = error_msg(filename);
	perror(file_error);
	free(file_error);
}

void	print_here_doc_error(char *delimiter)
{
	char	*text;

	text = " warning: here-document delimited by end-of-file";
	printf("%s (wanted '%s')\n", text, delimiter);
}

void	print_syntax_error(void)
{
	g_exit_status = 2;
	ft_putstr_fd("minishell: syntax error near unexpected token\n", 2);
}
