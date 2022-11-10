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

extern int	g_exit_status;

pid_t	create_fork(t_command *command, char **env)
{
	pid_t	child_id;

	child_id = fork();
	if (child_id == 0)
	{
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
		free_cmd_list(command, 1);
		free_str_tab(env);
		exit(2);
	}
	return (child_id);
}

void	execute_one_cmd(t_command *command, char **env)
{
	pid_t	child_id;
	int	status;
	
	if (command->av[0] != NULL)
	{
		if (command->path!= NULL)
		{
			child_id = create_fork(command, env);
			waitpid(child_id, &status, 0);
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
		}
		else
			printf("%s: command not found\n", command->av[0]);
	}
}
