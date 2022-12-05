/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:01:54 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/05 15:29:47 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	do_redirection(char **input, int *cmd_fd, int check)
{
	int	error;

	error = 1;
	if (what_separator(*input) == 1 && check == 1)
	{
		input++;
		error = input_redir(&cmd_fd[0], *input);
	}
	else if (what_separator(*input) == 2 && check == 1)
	{
		input++;
		error = output_redir(&cmd_fd[1], *input);
	}
	else if (what_separator(*input) == 3 && check == 1)
	{
		input++;
		error = here_doc_redir(&cmd_fd[0]);
	}
	else if (what_separator(*input) == 4 && check == 1)
	{
		input++;
		error = output_append(&cmd_fd[1], *input);
	}
	return (error);
}

int	output_redir(int *cmd_output_fd, const char *filename)
{
	int		file_fd;
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
	*cmd_output_fd = file_fd;
	return (file_fd);
}

int	output_append(int *cmd_output_fd, const char *filename)
{
	int		file_fd;
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

char	*error_msg2(const char *filename)
{
	char	*error_msg;

	error_msg = ft_strjoin("msh: ", filename);
	g_exit_status = 2;
	return (error_msg);
}

int	input_redir(int *cmd_input_fd, const char *filename)
{
	int		file_fd;
	char	*file_error;

	file_error = NULL;
	if (*cmd_input_fd != 0)
		close(*cmd_input_fd);
	file_fd = open(filename, O_RDONLY);
	if (file_fd == -1)
	{
		file_error = error_msg(filename);
		perror(file_error);
		*cmd_input_fd = -2;
		free(file_error);
		return (-2);
	}
	*cmd_input_fd = file_fd;
	return (file_fd);
}
