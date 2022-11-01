/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:58:00 by chjoie            #+#    #+#             */
/*   Updated: 2022/11/01 10:58:04 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include "../../includes/libft.h"
/*
void	create_fork(t_command command, char **envp)
{
	pid_t	child_id;

	child_id = fork();
	if (child_id == 0)
		execve(command.path, command.av, envp);
	waitpid(child_id, NULL, 0);
}
*/

void	execute_first_command(t_command command, int *pipefd)
{
	pid_t	child_id;
	
	pipe(pipefd);
	dup2(pipefd[1], 1);
	//close(pipefd[1]);
	//close(pipefd[0]);
	if (command.path != NULL)
	{
//		create_fork(command[i], NULL); //faire un getenv la dedans

		child_id = fork();
		if (child_id == 0)
		{
			execve(command.path, command.av, NULL);
		}
		waitpid(child_id, NULL, 0);
	}
	else
		printf("%s: command not found\n", command.av[0]);
}

void	execute_last_cmd(t_command command, int *pipefd)
{
	pid_t	child_id;

	//dup2(1, pipefd[1]);
	//close(1);
	dup2(pipefd[0], 0);
	close(pipefd[0]);
	child_id = fork();
	if (command.path != NULL)
	{
		if (child_id == 0)
		{
			execve(command.path, command.av, NULL);
		}
		waitpid(child_id, NULL, 0);
	}
	else
		printf("%s: command not found\n", command.av[0]);
}

void	execute_multiple_cmd(t_command *command, int cmd_amount)
{
	int	i;
	int	pipefd[2];
	int	pipefd2[2];
	
	i = 1;
	execute_first_command(command[0], pipefd);
	while (i < cmd_amount)
	{
		//if (i % 2 == 0 && (i < cmd_amount - 1))
		//	execute_even_cmd();
		//else if (i % 2 != 0 && (i < cmd_amount - 1))
		//	execute_odd_cmd();
		//else
		//{
			if (i % 2 != 0)
				execute_last_cmd(command[i], pipefd);
			else
				execute_last_cmd(command[i], pipefd2);
		//}
		i++;
	}
}
