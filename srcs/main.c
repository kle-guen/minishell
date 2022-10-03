/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:22:13 by kle-guen          #+#    #+#             */
/*   Updated: 2022/10/03 17:44:47 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

/**** ajout d'un '/' devant le nom de la commande pour que le chemin soit valide  ***/

char	*add_slash(char *str)
{
	char	*new_str;
	int		size;
	int		x;
	int		y;

	y = 0;
	x = 0;
	size = ft_strlen(str);
	new_str = malloc(sizeof(char)* size + 2);
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

int	my_strcmp(char *s1, char *s2)
{
	int	x;

	x = 0;
	if (!s1 || !s2)
		return (0);
	while ((s1[x] == s2[x]) && (s1[x] != '\0' && s2[x] != '\0'))
		x++;
	if (s1[x] == s2[x])
		return (x);
	return (0);
}

/***  si le fichier a le meme nom que la commande alors je retourne le chemin vers le fichier  ***/

char	*find_path(char *command, char *path)
{
	char	*command_path;

	command_path = NULL;
	command = add_slash(command);
	command_path = ft_strjoin(path, command);
	free(command);
	if (access(command_path, F_OK) == 0) //chemin absolu ou relatif deja valide
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
	while (tab_str[x])
	{
		free(tab_str[x]);
		tab_str[x] = NULL;
		x++;
	}
	free(tab_str);
	tab_str = NULL;
}

char	*get_path(char *command, char *path)
{
	char			**paths;  
	DIR				*ptr;
	int				x;
	char			*result; 

	result = NULL;
	x = 0;
	paths = ft_split(path, ':'); 
	while (paths[x] != NULL)
	{
		ptr = opendir(paths[x]); //ouvre un dossier dans *ptr
		if (ptr != NULL)
		{
				result = find_path(command, paths[x]); //check si c'est ce fichier qui execute la commande
				if (result != NULL)
				{
					closedir(ptr);
					free_str_tab(paths);
					return (result);
				}
		}
		closedir(ptr);
		x++;
	}
	free_str_tab(paths);
	return (result);
}

char	*parse_input(char *input)
{
	char	*parsed;

	parsed = input;
	return (parsed);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**cmd_args;
	char	*path;
	char	*command_path;

	path = getenv("PATH");
	(void) av;

	(void) env;

	if (ac == 1)
	{
		while (1)
		{
			input = readline("$> ");
			if (!input)
				break ;
			add_history(input);

			input = parse_input(input); // fonctions de parsing a faire

			cmd_args = ft_split(input, ' '); // rempli le tableau de la command avec les arguments
			command_path = NULL;
			if (cmd_args[0] != NULL)
			{
				if (access(cmd_args[0], F_OK) == 0) //chemin absolu ou relatif deja valide
					command_path = cmd_args[0];
				else
					command_path = get_path(cmd_args[0], path);
				if (command_path != NULL)
				//	printf("ok");
					execve(command_path, cmd_args, env);// executer dans un fork pour ne pqs stopper le program
				else
					printf("%s: command not found\n", cmd_args[0]);
			}
			free_str_tab(cmd_args);
			free(command_path);
	/****	variables d'environnement		*****/
		//	if (getenv(input) != NULL)
		//		printf("%s\n", getenv(input));
		}
	}
	printf("exit\n");
	return (0);
}
