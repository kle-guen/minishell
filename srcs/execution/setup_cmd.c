/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:43:43 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/05 15:43:04 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_fd(t_cmd *cmd_list, int cmd_amount)
{
	while (cmd_amount != 0)
	{
		cmd_amount--;
		if (cmd_list[cmd_amount].cmd_fd[0] != 0 && \
				cmd_list[cmd_amount].cmd_fd[0] != -2)
			close(cmd_list[cmd_amount].cmd_fd[0]);
		if (cmd_list[cmd_amount].cmd_fd[1] != 1)
			close(cmd_list[cmd_amount].cmd_fd[1]);
	}
}

void	launch_cmd(t_exec *execution)
{
	int	x;

	x = 0;
	if (execution->cmd_total == 1)
	{
		ft_reparsing(execution->cmd_list->av);
		execute_one_cmd(execution);
	}
	else
	{
		while (x < execution->cmd_total)
		{
			ft_reparsing(execution->cmd_list[x].av);
			x++;
		}
		execute_multiple_cmd(execution);
	}
}

void	clean_everything(t_exec *execution)
{
	free_str_tab(execution->env_str);
	unlink("/tmp/.here_doc_file");
	close_fd(execution->cmd_list, execution->cmd_total);
	free_cmd_list(execution->cmd_list, execution->cmd_total);
}

void	ft_execution(char **cmd_args, t_env *env_list)
{
	t_exec	execution;
	char	*path;

	if (check_after_parsing(cmd_args) == 0)
	{
		g_exit_status = 2;
		ft_putstr_fd("bash: syntax error near unexpected token\n", 2);
		return ;
	}
	execution = init_execution_structure(cmd_args, env_list);
	if (check_here_doc(cmd_args, execution.env) == 0)
		return ;
	execution.cmd_list = malloc(sizeof(t_cmd) * (execution.cmd_total));
	if (execution.cmd_list == NULL)
		return ;
	execution.env_str = get_exec_env(&env_list);
	if (!execution.env_str)
		return ;
	path = ft_get_env("PATH", execution.env);
	fill_cmds(&execution, path, cmd_args);
	if (g_exit_status != 1 && g_exit_status != 127)
		launch_cmd(&execution);
	clean_everything(&execution);
}
