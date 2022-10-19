/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 16:18:50 by chjoie            #+#    #+#             */
/*   Updated: 2022/10/19 17:05:56 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <fcntl.h>
#include <unistd.h>

void	input_redir(const char *command, char *filename)
{
	int	file_fd;
	char	*cmd[] = {"cat", filename, NULL}; //test

	file_fd = open(filename, O_RDONLY);
	printf("file descriptor is = %d\ncommand is %s\n", file_fd, command);
	dup2(file_fd, 0);
	close(file_fd);
	execve("/usr/bin/cat", cmd, NULL);
}

void	output_redir(const char *command, const char *filename, char **envp)
{
	int	file_fd;
	char *cmd[] = {"wc", "-l", "file1", NULL}; // test

	file_fd = open(filename, O_WRONLY | O_CREAT, 0600);
	printf("file descriptor is = %d\ncommand is %s\n", file_fd, command);
	dup2(file_fd, 1);
	close(file_fd);
	execve("/usr/bin/wc", cmd, envp);
}

void	input_append(const char *filename, const char *text)
{
	int	file_fd;

	file_fd = open(filename, O_RDWR | O_APPEND);
	printf("file fd is = %d\n", file_fd);
	write(file_fd, text, ft_strlen(text));
	close(file_fd);
}

//faire une structure pour stocker les commandes dans le bon format pour pouvoir les utiliser plus facilement dans toutes les fonctions

int	main(int ac, char **argv, char **envp)
{
	(void) envp;
	if (ac > 2)
	{
//		input_redir(argv[1], argv[2]);
//		output_redir(argv[1], argv[2], envp);
		input_append(argv[1], argv[2]);
	}
	return (0);
}
