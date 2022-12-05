/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:22:27 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/05 13:58:04 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_cmd_list(t_cmd *cmd_list, int size)
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
	int	size;
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

char	*fill_empty_opt(char *opt)
{
	char	*new_opt;

	free(opt);
	new_opt = malloc(sizeof(char) * 3);
	new_opt[0] = 39;
	new_opt[1] = 39;
	new_opt[2] = '\0';
	return (new_opt);
}

int	check_input(char *str)
{
	while (*str != '\0')
	{
		if (*str == '\"')
		{
			str++;
			if (ft_strchr(str, '\"') && (ft_strlen(str) > 1))
				return (2);
		}
		else if (*str == '\'')
		{
			str++;
			if (ft_strchr(str, '\'') && (ft_strlen(str) > 1))
				return (3);
		}
		else
			str++;
	}
	return (1);
}
