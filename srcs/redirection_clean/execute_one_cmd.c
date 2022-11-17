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


pid_t	create_fork(t_command *command, char **env)
{
	pid_t	child_id;

	child_id = fork();
	if (child_id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (command->cmd_fd[0] != 0)
		{
			dup2(command->cmd_fd[0], 0);
			close(command->cmd_fd[0]);
		}
		if (command->cmd_fd[1] != 1)
		{
			dup2(command->cmd_fd[1], 1);
			close(command->cmd_fd[1]);
		}
		execve(command->path, command->av, env);
		exit(2);
	}
	return (child_id);
}

void	execute_one_cmd(t_command *command, char **env)
{
	pid_t	child_id;
	int	status;
	
	if (command->av[0] != NULL && command->cmd_fd[0] != -2)
	{
		if (command->path!= NULL)
		{
			child_id = create_fork(command, env);
			waitpid(child_id, &status, 0);
			printf("exit status = %d\n" , status);
			if (WIFEXITED(status))
			{
				if (WEXITSTATUS(status))
				{
					g_exit_status = WEXITSTATUS(status);
				if (g_exit_status == 130)
					printf("\n");
				else if (g_exit_status == 131)
					printf("core dumped\n");
				}
			}
		}
		else
			printf("%s: command not found\n", command->av[0]);
	}
}
