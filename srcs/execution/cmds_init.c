/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:09:52 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/05 15:42:54 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_exec	init_execution_structure(char **cmd_args, t_env *env_list)
{
	t_exec	execution;

	execution.cmd_list = NULL;
	execution.child_id = NULL;
	execution.input = cmd_args;
	execution.env = env_list;
	execution.cmd_total = count_pipe(cmd_args) + 1;
	return (execution);
}

char	**get_cmd_opt(char **input)
{
	char	**cmd_opts;
	int		x;
	int		check;

	check = 1;
	x = 0;
	cmd_opts = malloc(sizeof(char **) * (get_opt_size(input) + 1));
	if (!cmd_opts)
		return (NULL);
	while (*input != NULL && is_pipe(*input) != 1)
	{
		check = check_input(*input);
		if (check == 4)
			cmd_opts[x++] = ft_strdup("''");
		else if (check != 1)
			cmd_opts[x++] = ft_strdup(*input);
		if (is_separator(*input) == 1 && check == 1)
			input++;
		else if (check == 1)
			cmd_opts[x++] = ft_strdup(*input);
		input++;
	}
	cmd_opts[x] = NULL;
	return (cmd_opts);
}

void	fill_cmds(t_exec *execution, char *path, char **input)
{
	int	x;

	x = 0;
	while (x < execution->cmd_total)
	{
		g_exit_status = 0;
		execution->cmd_list[x] = set_cmd(input, path);
		while (is_pipe(*input) == 0 && *input != NULL)
			input++;
		if (is_pipe(*input))
			input++;
		x++;
	}
}

t_cmd	set_cmd(char **input, char *path)
{
	t_cmd	command;
	int		check;

	check = 1;
	command.cmd_fd[0] = 0;
	command.cmd_fd[1] = 1;
	command.av = get_cmd_opt(input);
	command.path = get_path(command.av[0], path);
	while (*input != NULL)
	{
		check = check_input(*input);
		while (is_separator(*input) && is_pipe(*input) == 0)
		{
			if (do_redirection(input, command.cmd_fd, check) < 0)
				return (command);
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
