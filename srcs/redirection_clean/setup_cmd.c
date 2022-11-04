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
	int y;

	y = 0;
	x = 0;
	while (x < size)
	{
		y = 0;
		while (cmd_list[x].av[y] != NULL)
		{
			free(cmd_list[x].av[y]);
			y++;
		}
		free(cmd_list[x].path);
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
			if (do_redirection(input, command.cmd_fd) == -1)
				return (command);
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

void	launch_cmd(t_command *cmd_list, int cmd_amount)
{
	if (cmd_amount == 1)
		execute_one_cmd(cmd_list[0]);
	else
		execute_multiple_cmd(cmd_list, cmd_amount);
}

int	main(int ac, char **argv/*, char **envp*/)
{
	t_command *cmd_list;
	int	x;
	int	cmd_amount;
	
	char 	*path = getenv("PATH");
	
	x = 0;
	cmd_list = NULL;
	if (ac >= 2)
	{
		argv++; 
		cmd_amount = count_pipe(argv) + 1;
		cmd_list = malloc(sizeof(t_command) * (cmd_amount));
		while (x < cmd_amount)
		{
			cmd_list[x] = set_cmd(argv, path);

			while (is_pipe(*argv) == 0 && *argv != NULL)
				argv++;
			if (is_pipe(*argv))
				argv++;
			x++;
		}
		launch_cmd(cmd_list, cmd_amount);
	}
	free_cmd_list(cmd_list, cmd_amount);
}
