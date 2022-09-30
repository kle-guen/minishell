/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:22:13 by kle-guen          #+#    #+#             */
/*   Updated: 2022/09/30 15:34:24 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <dirent.h>
#include <readline/readline.h>
#include <stdio.h>
#include <string.h>

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

/***  si le fichier a le meme nom que la commande alors je retourne le chemin vers la commande  ***/
char	*find_path(char *dir_name, char *command, char *path)
{
	char	*command_path;

	command_path = NULL;
	if (!strncmp(dir_name, command, ft_strlen(dir_name)))
	{
		command = add_slash(command);
		command_path = ft_strjoin(path, command); //ajout free de *s1 dans le strjoin de ma libft
	}
	return (command_path);
}

void	free_path(char **tab_str)
{
	int	x;

	x = 0;
	while (tab_str[x])
	{
		free(tab_str[x]);
		x++;
	}
	free(tab_str);
}

char	*get_path(char *command, char *path)
{
	char			**paths;  
	DIR				*ptr;
	struct dirent	*dir;	
	int				x;
	char			*result; 

	result = NULL;
	x = 0;
	paths = ft_split(path, ':'); 
	while (paths[x] != NULL)
	{
		printf("path = %s\n", paths[x]);
		ptr = opendir(paths[x]); //ouvre un dossier dans *ptr
		if(ptr != NULL)
		{
			dir = readdir(ptr);		//check les fichiers du dossier en question
			while (dir != NULL)
			{
				result = find_path(dir->d_name, command, paths[x]); //check si c'est ce fichier qui execute la commande
				if (result != NULL)
				{
					closedir(ptr);
					free_path(paths);
					return (result);
				}
				dir = readdir(ptr);
			}
		}
		closedir(ptr);
		x++;
	}
	free_path(paths);
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
	char	*tab[3]; // besoin pour preciser les options des commands a executer avec execve()
	char	*path;
	char	*command_path;
	
	path = getenv("PATH");
	tab[0] = "ls";
	tab[1] = "-l";
	tab[1] = NULL;
	(void) av;
	if (ac == 1)
	{
		while (1)
		{
			input = readline("$> ");
			if (!input)
				break ;
			add_history(input);
			input = parse_input(input); // fonctions de parsing a faire
			command_path = get_path(input, path);
			if (command_path != NULL)
				execve(command_path, tab, env); // executer dans un fork pour ne pqs stopper le program
			//free le command_path apres l'execution dans le child
		}
	}
	printf("exit\n");
	return (0);
}
