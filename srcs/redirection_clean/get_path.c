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

int	check_if_directory(char *command)
{
// envoyer set global
// voir avec errono
	struct stat	path_stat;

	if (stat(command, &path_stat) == -1)
	{
		perror(command);
		if (errno == EACCES)
			printf("permission denied"); //global to 126
		return (1);
	}
	if (stat(command, &path_stat) == 0)
	{
		if (path_stat.st_mode & S_IFDIR)
		{
			printf("directory");
			return (1);
		}
		if (path_stat.st_uid != 0 && ft_strncmp(command, "./minishell", 11) != 0)
		{
			printf("not root exe");
			return (1);
		}
	}
//	else
//	{
//		if (errno == EACCES)
//			printf("permission denied"); //global to 126
		//else // 127
		
//	}
	return (0);
	
}

char	*get_path(char *command, char *path)
{
	char	**paths;
	int		x;
	char	*result;

	result = NULL;
	x = 0;
	if (command == NULL || path == NULL)
		return (NULL); //no such file or directory
	if (*command == '/' || *command == '.')
	{
		if (access(command, X_OK) == 0 && check_if_directory(command) == 0)
		{
			result = ft_strdup(command);
			return (result);
		}
		else
		{
			//perror(command);
			if (errno == EACCES)
				printf("permission denied"); // 126 else 127
			return (NULL); // no such file or directory
		}
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
