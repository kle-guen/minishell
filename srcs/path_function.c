/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:43:31 by chjoie            #+#    #+#             */
/*   Updated: 2022/10/04 16:51:24 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
	if (access(command_path, X_OK) == 0)
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
			result = find_path(command, paths[x]); //check si c'est ce fichier qui execute la commande
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

void	create_fork(char *command_path, char **cmd_args, char **envp)
{
	pid_t	child_id;

	child_id = fork();
	if (child_id != 0)
		waitpid(child_id, NULL, 0);
	if (child_id == 0)
		execve(command_path, cmd_args, envp);// executer dans un fork pour ne pqs stopper le program
}

void	execute_cmd(char *input, char **envp)
{
	char	**cmd_args;
	char	*path;
	char	*command_path;

	(void) envp;
	path = getenv("PATH");
	cmd_args = ft_split(input, ' ');
	command_path = NULL;
	if (cmd_args[0] != NULL)
	{
		if (access(cmd_args[0], F_OK) == 0)
			command_path = cmd_args[0];
		else
			command_path = get_path(cmd_args[0], path);
		if (command_path != NULL)
			create_fork(command_path, cmd_args, envp);
		else
			printf("%s: command not found\n", cmd_args[0]);
		free(command_path);
	}
	/**** voir pour free cmd_args avec fork car double free dans 1 cas... *****/
	free_str_tab(cmd_args);
	free(command_path);
}

// gerer les '' et ' ' comme bash
// voir pour la completion auto uniquement lorsque le cmd_[0] est une commande valide ?


