/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:58:00 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/05 15:14:15 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

pid_t	execute_first_command(t_minishell *execution, int *pipefd1, int cmd_nb)
{
	pid_t	child_id;

	child_id = 0;
	pipe(pipefd1);
	if (execution->cmd_list[cmd_nb].av[0] != NULL \
			&& execution->cmd_list[cmd_nb].cmd_fd[0] != -2)
	{
		if (execution->cmd_list[cmd_nb].path != NULL \
				|| ft_is_built_ins(execution->cmd_list[cmd_nb].av[0]))
		{
			child_id = fork();
			if (child_id == 0)
				execute_in_fork(execution, pipefd1, cmd_nb);
			close(pipefd1[1]);
		}
		else
			child_id = cmd_not_found1(execution, cmd_nb, pipefd1);
	}
	else
		close(pipefd1[1]);
	return (child_id);
}

pid_t	launch_cmd2(t_minishell *execution, int *pipe1, int *pipe2, int cmd_nb)
{
	pid_t	child_id;

	if (execution->cmd_list[cmd_nb].path != NULL \
			|| ft_is_built_ins(execution->cmd_list[cmd_nb].av[0]))
	{
		child_id = fork();
		if (child_id == 0)
		{
			ft_if_after_buitin(execution, cmd_nb);
			setup_middle_command(&execution->cmd_list[cmd_nb].cmd_fd[0], \
					&execution->cmd_list[cmd_nb].cmd_fd[1], pipe1, pipe2);
			close_pipe(pipe1);
			close_pipe(pipe2);
			execute(execution, cmd_nb);
		}
		close(pipe2[0]);
		close(pipe1[1]);
	}
	else
		child_id = not_found2(execution, cmd_nb, pipe1, pipe2);
	return (child_id);
}

pid_t	execute_cmd(t_minishell *execution, int *pipe1, int *pipe2, int cmd_nb)
{
	pid_t	child_id;

	child_id = 0;
	pipe(pipe1);
	if (execution->cmd_list[cmd_nb].av[0] != NULL \
			&& execution->cmd_list[cmd_nb].cmd_fd[0] != -2)
		child_id = launch_cmd2(execution, pipe1, pipe2, cmd_nb);
	else
	{
		close(pipe2[0]);
		close(pipe1[1]);
	}
	return (child_id);
}

pid_t	execute_last_cmd(t_minishell *execution, int *pipefd, int cmd_nb)
{
	pid_t	child_id;

	child_id = 0;
	if (execution->cmd_list[cmd_nb].av[0] != NULL \
			&& execution->cmd_list[cmd_nb].cmd_fd[0] != -2)
	{
		if (execution->cmd_list[cmd_nb].path != NULL \
				|| ft_is_built_ins(execution->cmd_list[cmd_nb].av[0]))
		{
			child_id = fork();
			if (child_id == 0)
				child_last_cmd(execution, pipefd, cmd_nb);
			else
				close_pipe(pipefd);
		}
		else
			child_id = cmd_not_found3(execution, cmd_nb, pipefd);
	}
	close_pipe(pipefd);
	return (child_id);
}

void	execute_multiple_cmd(t_minishell *execution)
{
	int	i;
	int	pipe1[2];
	int	pipe2[2];

	execution->child_id = malloc(sizeof(pid_t) * execution->cmd_total);
	i = 1;
	execution->child_id[0] = execute_first_command(execution, pipe1, 0);
	while (i < execution->cmd_total)
	{
		if (i % 2 == 0 && (i < execution->cmd_total - 1))
			execution->child_id[i] = execute_cmd(execution, pipe1, pipe2, i);
		else if (i % 2 != 0 && (i < execution->cmd_total - 1))
			execution->child_id[i] = execute_cmd(execution, pipe2, pipe1, i);
		else
		{
			if (i % 2 == 0)
				execution->child_id[i] = execute_last_cmd(execution, pipe2, i);
			else
				execution->child_id[i] = execute_last_cmd(execution, pipe1, i);
		}
		i++;
	}
	wait_child(execution->child_id, execution->cmd_total);
}
