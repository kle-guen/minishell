/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:43:31 by chjoie            #+#    #+#             */
/*   Updated: 2022/11/24 14:01:41 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

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
		free(command_path);
		return (NULL);
	}
}

int	check_directory(char *command)
{
	struct stat	path_stat;

	if (stat(command, &path_stat) == -1)
	{
		perror(command);
		if (errno == EACCES)
		{
			ft_putstr_fd("minishell: permission denied", 2);
			g_exit_status = 126;
		}
		return (1);
	}
	if (stat(command, &path_stat) == 0)
	{
		if (path_stat.st_mode & S_IFDIR)
		{
			g_exit_status = 126;
			ft_putstr_fd("minishell: Is a directory\n", 2);
			return (1);
		}
	}
	return (0);
}

char	*command_path(char *command, char *path)
{
	char	**paths;
	int		x;
	char	*result;

	result = NULL;
	paths = ft_split(path, ':');
	x = 0;
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
	return (result);
}

char	*get_path(char *command, char *path)
{
	char	*result;
	int		error;

	result = NULL;
	if (!command)
		return (NULL);
	error = check_directory_error(command);
	if (!access(command, X_OK) && error == 1)
	{
		result = ft_strdup(command);
		return (result);
	}	
	else if (!access(command, F_OK) && path == NULL)
	{
		error = check_directory_error(command);
		if (error == 2)
			return (NULL);
	}
	if (path == NULL)
		return (NULL);
	result = command_path(command, path);
	return (result);
}
