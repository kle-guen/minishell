/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_not_found.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:46:47 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/05 14:01:19 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

pid_t	cmd_not_found1(t_exec *execution, int cmd_nb, int *pipefd1)
{
	pid_t	child_id;

	child_id = fork();
	if (child_id == 0)
	{
		cmd_not_found(execution->cmd_list[cmd_nb].av[0]);
		close_pipe(pipefd1);
		ft_free_execution(execution);
		exit(127);
	}
	else
		close(pipefd1[1]);
	return (child_id);
}

pid_t	not_found2(t_exec *execution, int cmd_nb, int *pipe1, int *pipe2)
{
	pid_t	child_id;

	child_id = fork();
	if (child_id == 0)
	{
		cmd_not_found(execution->cmd_list[cmd_nb].av[0]);
		close_pipe(pipe1);
		close_pipe(pipe2);
		ft_free_execution(execution);
		exit(127);
	}
	else
	{
		close(pipe2[0]);
		close(pipe1[1]);
	}
	return (child_id);
}

pid_t	cmd_not_found3(t_exec *execution, int cmd_nb, int *pipefd)
{
	pid_t	child_id;

	child_id = fork();
	if (child_id == 0)
	{
		cmd_not_found(execution->cmd_list[cmd_nb].av[0]);
		close_pipe(pipefd);
		ft_free_execution(execution);
		exit(127);
	}
	else
		close_pipe(pipefd);
	return (child_id);
}

void	one_command_not_found(char	*cmd_name)
{
	if (g_exit_status != 126)
	{
		ft_putstr_fd(cmd_name, 2);
		ft_putstr_fd(": command not found\n", 2);
		g_exit_status = 127;
	}
}
