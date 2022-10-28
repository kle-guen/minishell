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

int	do_redirection(char **input, int *cmd_fd)
{
	int	error = 1;

	if (what_separator(*input) == 1)
	{
		input++;
		error = input_redir(&cmd_fd[0], *input);
	}
	else if (what_separator(*input) == 2)
	{
		input++;
		error = output_redir(&cmd_fd[1], *input);
	}
//	else if (commands->separator == 3)
//		heredoc;
	else if (what_separator(*input) == 4)
	{
		input++;
		error = output_append(&cmd_fd[1], *input);
	}
	return (error);
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

t_command	set_cmd(char **input)
{
	t_command	command;
	
	command.cmd_fd[0] = 0;
	command.cmd_fd[1] = 1;
	command.av = get_command_opt(input);

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
		input++;
	}
	return (command);
}

int	main(int ac, char **argv)
{
	t_command *cmd_list;
	int	x;
	int	cmd_amount;

	x = 0;
	cmd_list = NULL;
	if (ac >= 2)
	{
		argv++; //pour skip le ./a.out
		cmd_amount = count_pipe(argv) + 1;
		cmd_list = malloc(sizeof(t_command) * (cmd_amount));
		while (x < cmd_amount)
		{
			cmd_list[x] = set_cmd(argv);
		//	cmd_list[x].pipe_fd = pipefd;
			while (is_pipe(*argv) == 0 && *argv != NULL) //pour passer la la commande suivante
				argv++;
			if (is_pipe(*argv))
				argv++;
			x++;
		}


/*******   boucle pour le multipipe qui mqrche pas encore ****/

		int j = 0;
		int	pipefd[2];

		pipe(pipefd);	
		while (j < cmd_amount)
		{
			//if cmd > 1
			if (cmd_list[j].cmd_fd[0] == 0)
				cmd_list[j].cmd_fd[0] = pipefd[0];
			//else
			//	close(pipefd[0]);
			if (cmd_list[j].cmd_fd[1] == 1)
				cmd_list[j].cmd_fd[1] = pipefd[1];
			//else
			//	close(pipefd[1]);
			//dup2(pipefd[1], 1);
			execute_cmd(cmd_list[j]/*, pipefd*/);
			j++;
		}
		close(pipefd[0]);
		close(pipefd[1]);
	}
	free_cmd_list(cmd_list, cmd_amount);
}
