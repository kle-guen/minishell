/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_multiple_cmd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:58:00 by chjoie            #+#    #+#             */
/*   Updated: 2022/11/03 11:32:24 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include "../../includes/libft.h"

extern int	g_exit_status;

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

pid_t	execute_first_command(t_command command, int *pipefd1,char **env)
{
	pid_t	child_id;
	
	child_id = 0;
	pipe(pipefd1);
	if (command.path != NULL)
	{
		child_id = fork();
		if (child_id == 0)
		{
			set_outfile(&command.cmd_fd[1], pipefd1);
			set_infile(&command.cmd_fd[0], pipefd1);
			execve(command.path, command.av, env);
			exit(1);
		}
	}
	else
		printf("%s: command not found\n", command.av[0]);
	return (child_id);
}

pid_t	execute_cmd(t_command command, int *pipefd1, int *pipefd2, char **env)
{
	pid_t child_id;

	child_id = 0;
	pipe(pipefd1);
	if (command.path != NULL)
	{
		child_id = fork();
		if (child_id == 0)
		{
			set_infile(&command.cmd_fd[0], pipefd2);
			set_outfile(&command.cmd_fd[1], pipefd1);
			execve(command.path, command.av, env);
			exit(1);
		}
		close(pipefd2[0]);
		close(pipefd2[1]);
	}
	else
		printf("%s: command not found\n", command.av[0]);
	return (child_id);
}

pid_t	execute_last_cmd(t_command command, int *pipefd, char **env)
{
	pid_t	child_id;

	child_id = 0;
	if (command.path != NULL)
	{
		child_id = fork();
		if (child_id == 0)
		{
			set_infile(&command.cmd_fd[0], pipefd);
			set_outfile(&command.cmd_fd[1], pipefd);
			execve(command.path, command.av, env);
			exit(1);
		}
		else
		{
			close(pipefd[1]);
			close(pipefd[0]);
		}
	}
	else
		printf("%s: command not found\n", command.av[0]);
	return (child_id);
}

void	wait_child(pid_t *child_id, int cmd_amount)
{
	int	i;
	int	status;
	
	i = 0;
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

void	execute_multiple_cmd(t_command *command, int cmd_amount, char **env)
{
	int	i;
	int	pipefd1[2];
	int	pipefd2[2];
	pid_t	*child_id;
	
	child_id = malloc(sizeof(pid_t) * cmd_amount);
	i = 1;
	child_id[0] = execute_first_command(command[0], pipefd1, env);
	while (i < cmd_amount)
	{
		if (i % 2 == 0 && (i < cmd_amount - 1))
			child_id[i] = execute_cmd(command[i], pipefd1, pipefd2, env);
		else if (i % 2 != 0 && (i < cmd_amount - 1))
			child_id[i] = execute_cmd(command[i], pipefd2, pipefd1, env);
		else
		{
			if (i % 2 == 0)
				child_id[i] = execute_last_cmd(command[i], pipefd2, env);
			else
				child_id[i] = execute_last_cmd(command[i], pipefd1, env);
		}
		i++;
	}
	wait_child(child_id, cmd_amount);
}
