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

char	*error_msg(const char *filename)
{

// voir pour envoyer les error dans la function exec ?
	char *error_msg;
	
	error_msg = ft_strjoin("msh: ", filename);
	return (error_msg);  
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
