/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 13:43:31 by chjoie            #+#    #+#             */
/*   Updated: 2022/11/10 11:21:31 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <fcntl.h>

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
	if (access(command_path, X_OK) == 0)
		return (command_path);
	else
	{
		free(command_path);
		return (NULL);
	}
}

#include <sys/types.h>
#include <sys/stat.h>

int	check_valid_path(char *path)
{
// faire des trucs
// check si dossier
// envoyer set global
// voir avec errono
	struct stat	path_stat;

	if (stat(path, &path_stat) == 0)
	{
		if (path_stat.st_mode & S_IFDIR)
		{
			printf("directory");
			return (0);
		}
	}
	return (1);
}

char	*get_path(char *command, char *path)
{
	char	**paths;
	int		x;
	char	*result;

	result = NULL;
	x = 0;
	//if (check_valid_path(path) == 0)
	//	return (result);
	if (command == NULL)
		return (NULL);
	if (access(command, X_OK) == 0)
	{
		result = ft_strdup(command);
		return (result);
	}
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
	return (result);
}
