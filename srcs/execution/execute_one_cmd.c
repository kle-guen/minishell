/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:58:00 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/05 14:01:19 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_execution(t_exec *execution)
{
	close_fd(execution->cmd_list, execution->cmd_total);
	free_str_tab(execution->env_str);
	free_str_tab(execution->input);
	ft_free_env(&execution->env);
	free(execution->child_id);
	free_cmd_list(execution->cmd_list, execution->cmd_total);
}

void	set_cmd_fd(int fd_in, int fd_out)
{
	if (fd_in != 0)
	{
		dup2(fd_in, 0);
		close(fd_in);
	}
	if (fd_out != 1)
	{
		dup2(fd_out, 1);
		close(fd_out);
	}
}

pid_t	create_fork(t_exec *execution)
{
	pid_t	child_id;

	child_id = fork();
	if (child_id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		set_cmd_fd(execution->cmd_list->cmd_fd[0], \
				execution->cmd_list->cmd_fd[1]);
		if (ft_is_built_ins(execution->cmd_list->av[0]) == 1)
		{
			ft_built_ins_pipe(execution->cmd_list->av, &execution->env);
			ft_free_execution(execution);
			exit(0);
		}
		else
			execve(execution->cmd_list->path, \
					execution->cmd_list->av, execution->env_str);
		ft_free_execution(execution);
		exit(127);
	}
	return (child_id);
}

void	get_exit_status(int status)
{
	if (status == 131)
	{
		g_exit_status = 131;
		printf("core dumped\n");
	}
	else if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status))
		{
			g_exit_status = status;
			if (g_exit_status == 130)
				printf("\n");
			else if (g_exit_status == 131)
				printf("core dumped\n");
		}
	}
	else
		g_exit_status = 130;
}

void	execute_one_cmd(t_exec *execution)
{
	pid_t	child_id;
	int		status;

	if (execution->cmd_list->av[0] != NULL && \
			execution->cmd_list->cmd_fd[0] != -2)
	{
		if (!(ft_strncmp(execution->cmd_list->av[0], "exit", 4)))
			ft_exit_built(*execution->cmd_list, execution);
		else if (execution->cmd_list->path != NULL || \
				ft_is_built_ins(execution->cmd_list->av[0]))
		{
			g_exit_status = -1;
			child_id = create_fork(execution);
			waitpid(child_id, &status, 0);
			g_exit_status = 0;
			get_exit_status(status);
		}
		else
			one_command_not_found(execution->cmd_list->av[0]);
	}
}
