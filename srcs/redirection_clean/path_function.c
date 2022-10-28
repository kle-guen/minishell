/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:43:31 by chjoie            #+#    #+#             */
/*   Updated: 2022/10/28 10:50:22 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <unistd.h>

char	*add_slash(char *str)
{
	char	*new_str;
	int		size;
	int		x;
	int		y;

	y = 0;
	x = 0;
	size = ft_strlen(str);
	new_str = malloc(sizeof(char) * size + 2);
	if (!new_str)
		return (NULL);
	new_str[y] = '/';
	y++;
	while (str[x])
	{
		new_str[y] = str[x];
		x++;
		y++;
	}
	new_str[y] = '\0';
	return (new_str);
}

char	*find_path(char *command, char *path)
{
	char	*command_path;

	command_path = NULL;
	command = add_slash(command);
	command_path = ft_strjoin(path, command);
	free(command);
	if (access(command_path, F_OK) == 0)
		return (command_path);
	else
	{
		free (command_path);
		return (NULL);
	}
}

void	free_str_tab(char **tab_str)
{
	int	x;

	x = 0;
	if (tab_str != NULL)
	{
		while (tab_str[x])
		{
			free(tab_str[x]);
			tab_str[x] = NULL;
			x++;
		}
		free(tab_str);
		tab_str = NULL;
	}
}

char	*get_path(char *command, char *path)
{
	char	**paths;
	int		x;
	char	*result;

	result = NULL;
	x = 0;
	paths = ft_split(path, ':');
	while (paths[x] != NULL)
	{
			result = find_path(command, paths[x]);
			if (result != NULL)
			{
				free_str_tab(paths);
				return (result);
			}
		x++;
	}
	free_str_tab(paths);
	free(result);
	return (result);
}

void	create_fork(char *command_path, t_command cmd, char **envp)
{
	pid_t	child_id;

	child_id = fork();
	if (child_id == 0)
	{
		execve(command_path, cmd.av, envp);
	}
	waitpid(child_id, NULL, 0);
}

void	execute_cmd(t_command cmd_list/*, int *pipefd*//*, char **envp*/)
{
	char	*path;
	char	*command_path;

	//(void) envp;
	path = getenv("PATH");
	command_path = NULL;
	if (cmd_list.av[0] != NULL)
	{
		if (access(cmd_list.av[0], F_OK) == 0)
			command_path = cmd_list.av[0];
		else
			command_path = get_path(cmd_list.av[0], path);
		if (command_path != NULL)
			create_fork(command_path, cmd_list, NULL);
		else
			printf("%s: command not found\n", cmd_list.av[0]);
		free(command_path);
	}
}
//gerer meme command executer plusieurs fois?
//gerer les erreurs errno

// gerer les '' et ' ' comme bash

