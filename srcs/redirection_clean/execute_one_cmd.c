/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_one_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:58:00 by chjoie            #+#    #+#             */
/*   Updated: 2022/11/23 10:39:44 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

pid_t	create_fork(t_minishell *execution)
{
	pid_t	child_id;

	child_id = fork();
	if (child_id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (execution->cmd_list->cmd_fd[0] != 0)
		{
			dup2(execution->cmd_list->cmd_fd[0], 0);
			close(execution->cmd_list->cmd_fd[0]);
		}
		if (execution->cmd_list->cmd_fd[1] != 1)
		{
			dup2(execution->cmd_list->cmd_fd[1], 1);
			close(execution->cmd_list->cmd_fd[1]);
		}
			/*	if (is_built_in)
				{
					launch_built in pipe fct avec free (cmd_nb = 0)
				}
				else (execve), puis exit	
			*/
		//printf("lol");
		//free_str_tab(execution->env_str);
		//free_str_tab(execution->input);
		//ft_free_env(&execution->env);
		//free_cmd_list(execution->cmd_list, 1);
		//free();
		if (ft_is_built_ins(execution->cmd_list->av[0]))
			ft_built_ins(execution->cmd_list->av, &execution->env);
		else
			execve(execution->cmd_list->path, execution->cmd_list->av, execution->env_str);
		free_str_tab(execution->env_str);
		free_str_tab(execution->input);
		ft_free_env(&execution->env);
		free_cmd_list(execution->cmd_list, 1);
		//if (g_exit_status == -2)
		//	exit(0);
		exit(127);
	}
	return (child_id);
}

void	execute_one_cmd(t_minishell *execution)
{
	pid_t	child_id;
	int	status;
	
	if (execution->cmd_list->av[0] != NULL && execution->cmd_list->cmd_fd[0] != -2)
	{
		if (execution->cmd_list->path!= NULL || ft_is_built_ins(execution->cmd_list->av[0]))
		{
			g_exit_status = -1;
			child_id = create_fork(execution);
			waitpid(child_id, &status, 0);
			//printf("exit status = %d\n" , status);
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
		{
			if (g_exit_status != 126)
			{
				ft_putstr_fd(execution->cmd_list->av[0], 2);
				ft_putstr_fd(": command not found\n", 2);
				g_exit_status = 127;
			}	
		}
	}
}
