/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:43:43 by chjoie            #+#    #+#             */
/*   Updated: 2022/11/23 09:59:05 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

int	check_input(char *str);

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
	int	check;
	
	check = 1;
	x = 0;
	cmd_opts = NULL;
	cmd_opts = malloc(sizeof(char **) * (get_opt_size(input) + 1));
	if (!cmd_opts)
		return (NULL);
	while (*input != NULL && is_pipe(*input) != 1)
	{
		check = check_input(*input);
		if (check != 1)
		{
			//printf("besoin d'epur\n");
			if (check == 2)
				cmd_opts[x] = ft_strtrim(*input, "\"");
			else if (check == 3)
				cmd_opts[x] = ft_strtrim(*input, "\'");
			x++;
		}
		//else
		//{
			//printf("pas besoin d'epur\n");	
		//}
		if (is_separator(*input) == 1 && check == 1)
			input++;
		else if (check == 1)
		{
			cmd_opts[x] = ft_strdup(*input);
			x++;
		}
		input++;
	}
	cmd_opts[x] = NULL;
	return (cmd_opts);
}

int	check_input(char *str)
{
	while (*str != '\0')
	{
		if (*str == '"')
		{
			str++;
			if(ft_strchr(str, '\"') && (ft_strlen(str) > 1))
				return (2); //besoin d'epur
		}
		else if (*str == '\'')
		{
			str++;
			if(ft_strchr(str, '\'') && (ft_strlen(str) > 1))
				return (3); //besoin d'epur
		}
		str++;
	}
	return (1);
}

t_command	set_cmd(char **input, char *path)
{
	t_command	command;
	int		check;
	
	check = 1;
	command.cmd_fd[0] = 0;
	command.cmd_fd[1] = 1;
	command.av = get_command_opt(input);
	command.path = get_path(command.av[0], path);
	while (*input != NULL)
	{
		check = check_input(*input);
		while (is_separator(*input) && is_pipe(*input) == 0)
		{		
			//printf("check here bis = %d\n", check);
			if (do_redirection(input, command.cmd_fd, check) < 0)
			{
				return (command);
			}
			else
				input = input + 2;
		}
		if (is_pipe(*input) == 1)
			return (command);
		if (*input)
			input++;
	}
	return (command);
}

void	launch_cmd(t_minishell *execution, int cmd_amount)
{
	if (cmd_amount == 1)
		execute_one_cmd(execution);
	else
		execute_multiple_cmd(execution, cmd_amount);
}

void	clear_here_doc()
{
	pid_t	child_id;
	int	fd;
	char	*av[] = {"chmod", "644", "/tmp/.here_doc_file", NULL};
	
	fd = open("/tmp/.here_doc_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
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
	if (check_input(cmd_args[x]) == 1)
	{
	clear_here_doc();
	fd = open("/tmp/.here_doc_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (cmd_args[x] != NULL)
	{
		if (is_separator(cmd_args[x]) && what_separator(cmd_args[x]) == 3)
		{
			x++;
			delimiter = ft_strdup(cmd_args[x]);
			here_doc(delimiter, cmd_args, env_list, fd);
			free(delimiter);
			if (g_exit_status == -2)
			{
				g_exit_status = 130;
				unlink("/tmp/.here_doc_file");
				close(fd);
				return ;	
			}
		}
		x++;
	}
	close(fd);
	}
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

void	ft_execute_cmd(char **cmd_args, t_env *env_list)
{
	t_minishell	execution;
	int	x;
	int	cmd_amount;
	char 	*path;
	
	x = 0;
	execution.cmd_list = NULL;
	execution.child_id = NULL;
	execution.input = cmd_args;
	//execution.cmd_list.path = NULL;
	execution.env = env_list;
	cmd_amount = 0;
	g_exit_status = 0;

	/*if (check_after_parsing(cmd_args) == 0)
	{
		//free_str_tab(execution->env);
		g_exit_status = 2;
		ft_putstr_fd("msh : Symbol error\n", 2);
		return ;
	}*/
	check_here_doc(cmd_args, execution.env);
	//printf("%s cmd arg = ", cmd_args[0]);
	if (g_exit_status == 130) // besoin de reset
		return ;
	//g_exit_status = 130;
	path = ft_get_env("PATH", execution.env);
	cmd_amount = count_pipe(cmd_args) + 1;
	execution.cmd_list = malloc(sizeof(t_command) * (cmd_amount));
	execution.env_str = get_exec_env(&env_list);
	while (x < cmd_amount)
	{
		execution.cmd_list[x] = set_cmd(cmd_args, path);
		while (is_pipe(*cmd_args) == 0 && *cmd_args != NULL)
		{
			cmd_args++;
		}
		if (is_pipe(*cmd_args))
			cmd_args++;
		x++;
	}
	//free_str_tab(cmd_args);
	launch_cmd(&execution, cmd_amount);
	free_str_tab(execution.env_str);
	unlink("/tmp/.here_doc_file"); // fctn close fd (heredoc) command
	close_fd(execution.cmd_list, cmd_amount);
	free_cmd_list(execution.cmd_list, cmd_amount);
}
