/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:58:00 by chjoie            #+#    #+#             */
/*   Updated: 2022/11/03 11:32:24 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <unistd.h>

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

pid_t	execute_first_command(t_command command, int *pipefd1)
{
	pid_t	child_id;
	
	pipe(pipefd1);
	if (command.path != NULL)
	{
		//faire un getenv la dedansdd
		child_id = fork();
		if (child_id == 0)
		{
			set_outfile(&command.cmd_fd[1], pipefd1);
			set_infile(&command.cmd_fd[0], pipefd1);
			execve(command.path, command.av, NULL);
		}
	}
	else
		printf("%s: command not found\n", command.av[0]);
	return (child_id);
}

pid_t	execute_cmd(t_command command, int *pipefd1, int *pipefd2)
{
	pid_t child_id;

	pipe(pipefd1);
	if (command.path != NULL)
	{
		child_id = fork();
		if (child_id == 0)
		{
			set_infile(&command.cmd_fd[0], pipefd2);
			set_outfile(&command.cmd_fd[1], pipefd1);
			execve(command.path, command.av, NULL);
		}
		close(pipefd2[0]);
		close(pipefd2[1]);
	}
	else
		printf("%s: command not found\n", command.av[0]);
	return (child_id);
}

pid_t	execute_last_cmd(t_command command, int *pipefd)
{
	pid_t	child_id;

	if (command.path != NULL)
	{
		child_id = fork();
		if (child_id == 0)
		{
			set_infile(&command.cmd_fd[0], pipefd);
			set_outfile(&command.cmd_fd[1], pipefd);
			execve(command.path, command.av, NULL);
		}
		else
		{
			close(pipefd[1]);
			close(pipefd[0]);
		}
	}
	else
		printf("%s: command not found\n", command.av[0]);
	return (child_id);
}

void	wait_child(pid_t *child_id, int cmd_amount)
{
	int	i;
	
	i = 0;
	while (i < cmd_amount)
	{
		waitpid(child_id[i], NULL, 0);
		i++;
	}
	free(child_id);
}

void	execute_multiple_cmd(t_command *command, int cmd_amount)
{
	int	i;
	int	pipefd1[2];
	int	pipefd2[2];
	pid_t	*child_id;
	
	child_id = malloc(sizeof(pid_t) * cmd_amount);
	i = 1;
	child_id[0] = execute_first_command(command[0], pipefd1);
	while (i < cmd_amount)
	{
		if (i % 2 == 0 && (i < cmd_amount - 1))
			child_id[i] = execute_cmd(command[i], pipefd1, pipefd2);
		else if (i % 2 != 0 && (i < cmd_amount - 1))
			child_id[i] = execute_cmd(command[i], pipefd2, pipefd1);
		else
		{
			if (i % 2 == 0)
				child_id[i] = execute_last_cmd(command[i], pipefd2);
			else
				child_id[i] = execute_last_cmd(command[i], pipefd1);
		}
		i++;
	}
	wait_child(child_id, cmd_amount);
}
