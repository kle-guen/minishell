/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:01:54 by chjoie            #+#    #+#             */
/*   Updated: 2022/10/26 11:01:55 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include "../../includes/libft.h"

int	do_redirection(char **input, int *cmd_fd)
{
	int	error = 1;

	if (what_separator(*input) == 1)
	{
		input++;
		error = input_redir(&cmd_fd[0], *input);
	}
	else if (what_separator(*input) == 2)
	{
		input++;
		error = output_redir(&cmd_fd[1], *input);
	}
//	else if (commands->separator == 3)
//		heredoc;
	else if (what_separator(*input) == 4)
	{
		input++;
		error = output_append(&cmd_fd[1], *input);
	}
	return (error);
}

int	output_redir(int *cmd_output_fd, const char *filename)
{
	int	file_fd;
	char	*file_error;

	file_error = NULL;
	if (*cmd_output_fd != 1)
		close(*cmd_output_fd);
	file_fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file_fd == -1)
	{	
		file_error = error_msg(filename);
		perror(file_error);
		free(file_error);
		return (file_fd);
	}
	//dup2(file_fd, 1); A FAIRE AVANT EXEC LA CMD
	*cmd_output_fd = file_fd;
	return (file_fd);
}

int	output_append(int *cmd_output_fd, const char *filename)
{
	int	file_fd;
	char	*file_error;
	
	file_error = NULL;
	if (*cmd_output_fd != 1)
		close(*cmd_output_fd);
	file_fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (file_fd == -1)
	{	
		file_error = error_msg(filename);
		perror(file_error);
		free(file_error);
		return (file_fd);
	}
	*cmd_output_fd = file_fd;
	return (file_fd);
}

int	input_redir(int *cmd_input_fd, const char *filename)
{
	int	file_fd;
	char	*file_error;
	
	file_error = NULL;
	if (*cmd_input_fd != 0)
		close(*cmd_input_fd);
	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
	{	
		file_error = error_msg(filename);
		perror(file_error);
		free(file_error);
		return (file_fd);
	}
	*cmd_input_fd = file_fd;
	return (file_fd);
}
