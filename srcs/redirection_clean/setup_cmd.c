/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:43:43 by chjoie            #+#    #+#             */
/*   Updated: 2022/10/27 15:56:07 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include "../../includes/libft.h"

void	free_cmd_list(t_command *cmd_list, int size)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	if (cmd_list[x].cmd_fd[0] != 0 && cmd_list[x].cmd_fd[0] != -2)
		close(cmd_list[x].cmd_fd[0]);
	while (x < size)
	{
		y = 0;
		while (cmd_list[x].av[y] != NULL)
		{
			free(cmd_list[x].av[y]);
			cmd_list[x].av[y] = NULL;
			y++;
		}
		free(cmd_list[x].path);
		cmd_list[x].path = NULL;
		free(cmd_list[x].av);
		x++;
	}
	free(cmd_list);
}

int	count_pipe(char **input)
{
	int	x;
	int	pipe_amount;

	pipe_amount = 0;
	x = 0;
	while (input[x] != NULL)
	{
		if (is_pipe(input[x]))
			pipe_amount++;
		x++;
	}
	return (pipe_amount);
}

int	get_opt_size(char **input)
{
	int size;
	int	x;
	
	x = 0;
	size = 0;
	while (input[x] != NULL && is_pipe(input[x]) != 1)
	{
		if (is_separator(input[x]) == 0)
			size++;
		else
			x++;
		x++;
	}
	return (size);
}

char	**get_command_opt(char **input)
{
	char	**cmd_opts;
	int		x;

	x = 0;
	cmd_opts = NULL;
	cmd_opts = malloc(sizeof(char **) * (get_opt_size(input) + 1));
	if (!cmd_opts)
		return (NULL);
	while (*input != NULL && is_pipe(*input) != 1)
	{
		if (is_separator(*input) == 1)
			input++;
		else
		{
			cmd_opts[x] = ft_strdup(*input);
			x++;
		}
		input++;
	}
	cmd_opts[x] = NULL;
	return (cmd_opts);
}

t_command	set_cmd(char **input, char *path)
{
	t_command	command;
	
	command.cmd_fd[0] = 0;
	command.cmd_fd[1] = 1;
	command.av = get_command_opt(input);
	command.path = get_path(command.av[0], path);
	while (*input != NULL)
	{
		while (is_separator(*input) && is_pipe(*input) == 0)
		{
			if (do_redirection(input, command.cmd_fd) < 0)
			{	
				return (command);
			}
			else
				input = input + 2;
		}
		if (is_pipe(*input) == 1)
			return (command) ;
		if (*input)
			input++;
	}
	return (command);
}

void	launch_cmd(t_command *cmd_list, int cmd_amount, char **my_envp)
{
	if (cmd_amount == 1)
		execute_one_cmd(cmd_list, my_envp);
	else
		execute_multiple_cmd(cmd_list, cmd_amount, my_envp);
}

void	clear_here_doc()
{
	pid_t	child_id;
	int	fd;
	char	*av[] = {"chmod", "777", "/tmp/here_doc_file", NULL};
	
	fd = open("/tmp/here_doc_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
	printf("le fd vaut %d\n", fd);
	if (fd == -1)
	{
		child_id = fork();
		if (child_id == 0)
		{
			execve("/usr/bin/chmod", av, NULL);

		}
	}
	wait(&child_id);
	if (fd != -1)
		close(fd);
}

void	check_here_doc(char **cmd_args, t_env *env_list)
{
	int	x;
	char	*delimiter;
	int	fd; 
	
	delimiter = NULL;
	x = 0;
	clear_here_doc();
	fd = open("/tmp/here_doc_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (cmd_args[x] != NULL)
	{
		if (what_separator(cmd_args[x]) == 3)
		{
			x++;
			delimiter = ft_strdup(cmd_args[x]);
			printf("exit status = %d \n", g_exit_status);
			here_doc(delimiter, cmd_args, env_list, fd);
			free(delimiter);
			if (g_exit_status == -2)
			{
				g_exit_status = 130;
				unlink("/tmp/here_doc_file");
				close(fd);
				return ;	
			}
		}
		x++;
	}
	close(fd);
}

void	close_fd(t_command *cmd_list, int cmd_amount)
{
	while (cmd_amount != 0)
	{
		cmd_amount--;
		if (cmd_list[cmd_amount].cmd_fd[0] != 0 && cmd_list[cmd_amount].cmd_fd[0] != -2)
			close(cmd_list[cmd_amount].cmd_fd[0]);
		if (cmd_list[cmd_amount].cmd_fd[1] != 1)
			close(cmd_list[cmd_amount].cmd_fd[1]);
	}
}

/*
int	check_fd_cmd(t_command *command)
{
	printf("cmd fd = %d\n", command->cmd_fd[0]);
	if (command->cmd_fd[0] == -2)
		return (0);
	return (1);
}*/

void	ft_execute_cmd(char **cmd_args, t_env *env_list)
{
	t_command *cmd_list;
	int	x;
	int	cmd_amount;
	char	**my_envp;
	char 	*path;

	x = 0;
	cmd_list = NULL;
	path = NULL;
	my_envp = NULL;
	cmd_amount = 0;

	check_here_doc(cmd_args, env_list);
	if (g_exit_status == 130)
		return ;
	path = ft_get_env("PATH", env_list);
	cmd_amount = count_pipe(cmd_args) + 1;
	cmd_list = malloc(sizeof(t_command) * (cmd_amount));
	my_envp = get_exec_env(&env_list);
	while (x < cmd_amount)
	{
		cmd_list[x] = set_cmd(cmd_args, path);
	/*	if (check_fd_cmd(&cmd_list[x]) == 0)
		{
			//printf("here");
			//free_cmd_list(cmd_list, x + 1);
			//free_str_tab(my_envp);
			//return ;
		}*/
		while (is_pipe(*cmd_args) == 0 && *cmd_args != NULL)
		{
			cmd_args++;
		}
		if (is_pipe(*cmd_args))
			cmd_args++;
		x++;
	}
	launch_cmd(cmd_list, cmd_amount, my_envp);
	free_str_tab(my_envp);
	unlink("/tmp/here_doc_file"); // fctn close fd (heredoc) command
	close_fd(cmd_list, cmd_amount);
	free_cmd_list(cmd_list, cmd_amount);
}
