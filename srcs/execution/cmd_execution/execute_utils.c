/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:51:28 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/05 15:29:33 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	print_not_found(char *cmd_name)
{
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": command not found\n", 2);
}

void	close_pipe(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
}

void	wait_child(pid_t *child_id, int cmd_amount)
{
	int	i;
	int	status;

	i = 0;
	g_exit_status = -1;
	while (i < cmd_amount)
	{
		waitpid(child_id[i], &status, 0);
		if (child_id[i] != 0)
		{
			if (WIFEXITED(status))
				g_exit_status = WEXITSTATUS(status);
		}
		else
			g_exit_status = 127;
		i++;
	}
	free(child_id);
}

void	execute_in_fork(t_exec *execution, int *pipefd1, int cmd_nb)
{
	setup_first_cmd(&execution->cmd_list[cmd_nb].cmd_fd[0], \
		&execution->cmd_list[cmd_nb].cmd_fd[1], pipefd1);
	execute(execution, cmd_nb);
	close_pipe(pipefd1);
	ft_free_execution(execution);
	exit(1);
}

void	execute(t_exec *execution, int cmd_nb)
{
	if (!(ft_strncmp(execution->cmd_list[cmd_nb].av[0], "exit", 5)))
	{
		ft_free_execution(execution);
		exit (0);
	}
	if (ft_is_built_ins(execution->cmd_list[cmd_nb].av[0]))
	{
		ft_built_ins_pipe(execution->cmd_list[cmd_nb].av, &execution->env);
		ft_free_execution(execution);
		exit (0);
	}
	else
		execve(execution->cmd_list[cmd_nb].path, \
				execution->cmd_list[cmd_nb].av, execution->env_str);
}
