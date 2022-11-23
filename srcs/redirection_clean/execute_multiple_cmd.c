/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:58:00 by chjoie            #+#    #+#             */
/*   Updated: 2022/11/23 06:23:40 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	get_env_size(t_env **root)
{
	int	i;
	t_env	*list;
	
	list = *root;
	i = 0;
	while (list->next)
	{
		list = list->next;
		i++;
	}
	i++;	
	return (i);
}

char	**get_exec_env(t_env **root)
{
	char	**env;
	t_env	*list;
	char	*start;
	int	i;
	
	list = *root;
	env = malloc(sizeof(char **) * (get_env_size(root) + 1));
	i = 0;
	while (list->next)
	{
		start = ft_strjoin(list->key, "=");
		env[i] = ft_strjoin(start, list->value);
		free(start);
		list = list->next;
		i++;
	}
	start = ft_strjoin(list->key, "=");
	env[i] = ft_strjoin(start, list->value);
	i++;
	env[i] = NULL;
	free(start);
	return (env);
}

pid_t	execute_first_command(t_minishell *execution, int *pipefd1, int cmd_nb)
{
	pid_t	child_id;
	
	child_id = 0;
	pipe(pipefd1);
	if (execution->cmd_list[cmd_nb].av[0] != NULL && execution->cmd_list[cmd_nb].cmd_fd[0] != -2)
	{
		if (execution->cmd_list[cmd_nb].path != NULL || ft_is_built_ins(execution->cmd_list[cmd_nb].av[0]))
		{
			child_id = fork();
			if (child_id == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				set_outfile(&execution->cmd_list[cmd_nb].cmd_fd[1], pipefd1);
				set_infile(&execution->cmd_list[cmd_nb].cmd_fd[0], pipefd1);
				if (ft_is_built_ins(execution->cmd_list[cmd_nb].av[0]))
					ft_built_ins(execution->cmd_list[cmd_nb].av, &execution->env);
				else
					execve(execution->cmd_list[cmd_nb].path, execution->cmd_list[cmd_nb].av, execution->env_str);
				exit(1);
			}
		}
		else
		{
			ft_putstr_fd(execution->cmd_list[cmd_nb].av[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
	}
	return (child_id);
}

pid_t	execute_cmd(t_minishell *execution, int *pipefd1, int *pipefd2, int cmd_nb)
{
	pid_t child_id;

	child_id = 0;
	pipe(pipefd1);
	if (execution->cmd_list[cmd_nb].av[0] != NULL && execution->cmd_list[cmd_nb].cmd_fd[0] != -2)
	{
		if (execution->cmd_list[cmd_nb].path != NULL || ft_is_built_ins(execution->cmd_list[cmd_nb].av[0]))
		{
			child_id = fork();
			if (child_id == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				set_infile(&execution->cmd_list[cmd_nb].cmd_fd[0], pipefd2);
				set_outfile(&execution->cmd_list[cmd_nb].cmd_fd[1], pipefd1);
				if ( ft_is_built_ins(execution->cmd_list[cmd_nb].av[0]))
					ft_built_ins(execution->cmd_list[cmd_nb].av, &execution->env);
				else
					execve(execution->cmd_list[cmd_nb].path, execution->cmd_list[cmd_nb].av, execution->env_str);
				exit(1);
			}
			close(pipefd2[0]);
			close(pipefd2[1]);
		}
		else
		{
			ft_putstr_fd(execution->cmd_list[cmd_nb].av[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
	}
	close(pipefd2[0]);
	close(pipefd2[1]);
	return (child_id);
}

pid_t	execute_last_cmd(t_minishell *execution, int *pipefd, int cmd_nb)
{
	pid_t	child_id;

	child_id = 0;
	if (execution->cmd_list[cmd_nb].av[0] != NULL && execution->cmd_list[cmd_nb].cmd_fd[0] != -2)
	{
		if (execution->cmd_list[cmd_nb].path != NULL || ft_is_built_ins(execution->cmd_list[cmd_nb].av[0]))
		{
			child_id = fork();
			if (child_id == 0)
			{
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				set_infile(&execution->cmd_list[cmd_nb].cmd_fd[0], pipefd);
				set_outfile(&execution->cmd_list[cmd_nb].cmd_fd[1], pipefd);
				if ( ft_is_built_ins(execution->cmd_list[cmd_nb].av[0]))
					ft_built_ins(execution->cmd_list[cmd_nb].av, &execution->env);
				else
					execve(execution->cmd_list[cmd_nb].path, execution->cmd_list[cmd_nb].av, execution->env_str);
				exit(1);
			}
			else
			{
				close(pipefd[1]);
				close(pipefd[0]);
			}
		}
		else
		{
			ft_putstr_fd(execution->cmd_list[cmd_nb].av[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
	}
	close(pipefd[0]);
	close(pipefd[1]);
	return (child_id);
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

void	execute_multiple_cmd(t_minishell *execution, int cmd_amount)
{
	int	i;
	int	pipefd1[2];
	int	pipefd2[2];
	
	execution->child_id = malloc(sizeof(pid_t) * cmd_amount);
	i = 1;
	execution->child_id[0] = execute_first_command(execution, pipefd1, 0);
	while (i < cmd_amount)
	{
		if (i % 2 == 0 && (i < cmd_amount - 1))
			execution->child_id[i] = execute_cmd(execution, pipefd1, pipefd2, i);
		else if (i % 2 != 0 && (i < cmd_amount - 1))
			execution->child_id[i] = execute_cmd(execution, pipefd2, pipefd1, i);
		else
		{
			if (i % 2 == 0)
				execution->child_id[i] = execute_last_cmd(execution, pipefd2, i);
			else
				execution->child_id[i] = execute_last_cmd(execution, pipefd1, i);
		}
		i++;
	}
	wait_child(execution->child_id, cmd_amount);
}
