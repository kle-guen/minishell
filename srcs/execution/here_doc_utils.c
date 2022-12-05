/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:04:12 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/01 16:04:13 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	ctrl_here(int signal)
{	
	(void) signal;
	g_exit_status = -2;
	close(0);
	printf("\n");
}

void	ft_free_here_doc(char *line, char *delimiter, int fd, int code)
{
	free(line);
	close(fd);
	free(delimiter);
	exit(code);
}

void	launch_here_doc(char **cmd_args, t_env *env_list, int fd, int x)
{
	char	*delimiter;

	delimiter = ft_strdup(cmd_args[x]);
	here_doc(delimiter, cmd_args, env_list, fd);
	free(delimiter);
}

void	close_here_doc(int fd)
{
	g_exit_status = 130;
	unlink("/tmp/.here_doc_file");
	close(fd);
}

void	clear_here_doc(void)
{
	pid_t	child_id;
	int		fd;
	char	*av[4];

	av[0] = "chmod";
	av[1] = "644";
	av[2] = "/tmp/.here_doc_file";
	av[3] = NULL;
	fd = open("/tmp/.here_doc_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		child_id = fork();
		if (child_id == 0)
			execve("/usr/bin/chmod", av, NULL);
	}
	wait(&child_id);
	if (fd != -1)
		close(fd);
}
