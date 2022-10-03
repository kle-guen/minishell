/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:22:13 by kle-guen          #+#    #+#             */
/*   Updated: 2022/10/03 14:36:24 by chjoie           ###   ########.fr       */
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

char	*find_path(char *dir_name, char *command, char *path)
{
	char	*command_path;

	command_path = NULL;
	if (my_strcmp(dir_name, command) != 0)
	{
		command = add_slash(command);
	//	printf("%s\n", command);
		command_path = ft_strjoin(path, command); //ajout free de *s1 dans le strjoin de ma libft
	}
	return (command_path);
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
	struct dirent	*dir;	
	int				x;
	char			*result; 

	result = NULL;
	x = 0;
	paths = ft_split(path, ':'); 
	while (paths[x] != NULL)
	{
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
					free_str_tab(paths);
					return (result);
				}
				dir = readdir(ptr);
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

int	count_equal(char *content)
{
	int	count;

	count = 0;
	while(content[count] != '\0' && content[count] != '=')
		count++;
	return (count);
}
/*
void	print_content(char *input)
{
	char	*content;

	content = getenv(input);
	printf("%s\n", content);

}
*/
int	main(int ac, char **av, char **env)
{
	char	*input;
	char	**cmd_args;
	char	*path;
	char	*command_path;

	path = getenv("PATH");
	(void) av;

	(void) command_path;
	(void) path;
	(void) cmd_args;
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

			if (access(cmd_args[0], F_OK) == 0) //chemin absolu ou relatif deja valide
				command_path = cmd_args[0];
			else
				command_path = get_path(cmd_args[0], path);
			if (command_path != NULL)
				execve(command_path, cmd_args, env);// executer dans un fork pour ne pqs stopper le program
			else
				printf("%s: command not found\n", cmd_args[0]);
			//free le command_path apres l'execution de la commande dans le child
			free_str_tab(cmd_args);
			
		
	/****	variables d'environnement		*****/
		//	if (getenv(input) != NULL)
		//		printf("%s\n", getenv(input));
		}
	}
	printf("exit\n");
	return (0);
}
