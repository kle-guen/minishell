/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:47:38 by chjoie            #+#    #+#             */
/*   Updated: 2022/10/18 15:50:52 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include "../../includes/libft.h"

int	is_double_char(char *str)
{	
	int	index;

	index = 1;
	if ((str[index - 1] == '>' && str[index]))
	{
		if (str[index] == '>' && str[index])
			index++;
		if (str[index] == '\0')
			return 1;
	}
	else if ((str[index - 1] == '<' && str[index]))
	{
		if (str[index] == '<' && str[index])
			index++;
		if (str[index] == '\0')
			return 1;
	}
	return (0);
}

int	check_separator(char *str)
{
	str++;
	if (*str == '\0')
		return (1);
	return (0);
}

int	is_separator(char *str)
{
	int is_separator;
	int	x;

	x = 0;
	is_separator = 0;
	if ((str[x] == '|' || str[x] == '>' || str[x] == '<') && *str)
	{
		x++;
		if (str[x] == '\0')
			return (1);
	}
	is_separator = is_double_char(str);
	return (is_separator);
}

int	get_cmd_size(char **input)
{
	int	x;
	int	size;

	size = 0;
	x = 0;
	while (input[x] != NULL)
	{
		if (is_separator(input[x]) == 0)
			size++;
		x++;
	}
	return (size);
}

char	***get_commands(char **input)
{
	char ***all_cmd = NULL;
	int		size;
	int		x;
	
	x = 0;
	size = get_cmd_size(input);
	all_cmd = malloc(sizeof(char **) * size + 1);

	while (x <= size)
	{
		if (is_separator(input[x]) == 1) // voir pour ne pas skip l'element mais le gerer 
			x++;
		all_cmd[x] = ft_split(input[x], ' ');
		x++;
	}
	all_cmd[x] = NULL;
	return (NULL);
}

int	main(int ac, char **av)
{
	if (ac >= 2)
	{
		av++;
		get_commands(av);
	}
	return (0);
	
}
