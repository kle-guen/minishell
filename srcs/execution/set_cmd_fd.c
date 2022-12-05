/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:43:29 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/05 15:29:51 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	set_outfile(int *cmd_outfile, int *pipefd)
{
	if (*cmd_outfile == 1)
	{
		dup2(pipefd[1], 1);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	else
	{
		dup2(*cmd_outfile, 1);
		close(*cmd_outfile);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	set_infile(int *cmd_infile, int *pipefd)
{
	if (*cmd_infile == 0)
	{
		dup2(pipefd[0], 0);
		close(pipefd[0]);
		close(pipefd[1]);
	}
	else
	{
		dup2(cmd_infile[0], 0);
		close(*cmd_infile);
		close(pipefd[0]);
		close(pipefd[1]);
	}
}

void	setup_last_cmd(int *fd_in, int *fd_out, int *pipefd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	set_infile(fd_in, pipefd);
	set_outfile(fd_out, pipefd);
}

void	setup_first_cmd(int *fd_in, int *fd_out, int *pipefd)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	set_outfile(fd_out, pipefd);
	set_infile(fd_in, pipefd);
}

void	setup_middle_command(int *fd_in, int *fd_out, int *pipe1, int *pipe2)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	set_outfile(fd_out, pipe1);
	set_infile(fd_in, pipe2);
}
