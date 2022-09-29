/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:22:13 by kle-guen          #+#    #+#             */
/*   Updated: 2022/09/29 18:38:01 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <dirent.h>
#include <stdio.h>
#include <string.h>

/**** j'ajoute un '/' devant le nom de la commande pour que le chemin soit valide  ***/
char	*add_slash(char *str)
{
	char	*new_str;
	int		size;
	int		x;
	int		y;

	y = 0;
	x = 0;
	size = ft_strlen(str);
	new_str = ft_calloc(sizeof(char), size + 3);
	new_str[y] = '/';
	y++;
	while (str[x])
	{
		new_str[y] = str[x];
		x++;
		y++;
	}
	y++;
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
		command_path = ft_strjoin(path, command);
	}
	return (command_path);
}

char	*get_path(char *command, char *path)
{
	char			**paths; // tous les chemins où peuvent etre localiser les commands 
	DIR				*ptr;	// pointeur sur un dossier (voir man de "opendir")
	struct dirent	*dir;	// poiteurs sur un ficher du dossier -> on peut recuperer le nom du fichier avec d_name (man readdir)
	int				x;
	char			*result; 

	x = 0;
	paths = ft_split(path, ':'); // recupere tous les chemins possibles
	while (paths[x++] != NULL)
	{
		if (strstr(paths[x], "nfs") == 0) //j'ai enleve les dossier nfs parce que on y a pas acces et ca faisait un segfault
		{
			ptr = opendir(paths[x]); //ouvre un dossier dans *ptr
			dir = readdir(ptr);		//check les fichiers du dossier en question
			while (dir != NULL)
			{
				result = find_path(dir->d_name, command, paths[x]); //check si c'est ce fichier qui execute la commande
				if (result != NULL)
					return (result);
			dir = readdir(ptr);
			}
			closedir(ptr);
		}
	}
	return (NULL);
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
			execve(command_path, tab, env); //voir comment ca marche car la foction arrete la boucle while
		}
	}
	printf("exit\n");
	return (0);
}
