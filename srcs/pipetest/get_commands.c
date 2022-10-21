/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:47:38 by chjoie            #+#    #+#             */
/*   Updated: 2022/10/21 14:12:16 by chjoie           ###   ########.fr       */
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
	if (str[x] == '\0')
		return (is_separator);
	if ((str[x] == '|' || str[x] == '>' || str[x] == '<'))
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

int	double_char_separator(const char *separator)
{
	int	symbol;
	int	x;

	x = 0;
	symbol = 0;
		if (separator[x] == '<')
			symbol = 4;
		else if (separator[x] == '>')
			symbol = 5;
	return (symbol);
}

int	what_separator(const char *separator)
{
	int	symbol;
	int	x;

	x = 0;
	symbol = 0;
	if (separator[x] == '|')
		symbol = 1;
	else if (separator[x] == '<' && separator[x + 1] == '\0')
		symbol = 2;
	else if (separator[x] == '>' && separator[x + 1] == '\0')
		symbol = 3;
	else
		symbol = double_char_separator(separator);
	return (symbol);
}

void	set_opts(t_cmd_opt *commands)
{
	int	x;
	int	first_sep;

	first_sep = 0;
	x = 0;
	commands->opt = 0;
	commands->next_opt = 0;
	while (commands->cmd_line[x] != NULL && first_sep == 0)
	{
		if (is_separator(commands->cmd_line[x][0]) == 1)
		{
			if (commands->cmd_line[x][1] == NULL)
			{
				commands->opt = what_separator(commands->cmd_line[x][0]);// a coder
				first_sep = 1;
			}
		}
		x++;
	}
	while (commands->cmd_line[x] != NULL && first_sep == 1)
	{
		if (is_separator(commands->cmd_line[x][0]) == 1)
		{
			if (commands->cmd_line[x][1] == NULL)
				commands->next_opt = 1;
		}
		x++;
	}

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
		all_cmd[x] = ft_split(input[x], ' '); // voir pour gerer les ' ' ?
		x++;
	}
	all_cmd[x] = NULL;
	return (all_cmd);
}


/** recupere la line de commande apres le parsing, 
 * je la stocke un tableau qui contient les commandes (avec leur arg) a executer (***cmd_line dans une struct)
 * si je tombe sur un pipe, ou un charactere de redirection je me un flag (je set opt dans la struct) pour savoir comment gerer la commande a executer
 * tant qu'il y a un pipe ou autre a gerer (next_opt) je refait la meme
 */

int	main(int ac, char **av)
{
	t_cmd_opt *commands;
	commands = malloc(sizeof(t_cmd_opt));
	if (ac >= 2)
	{
		av++;
		commands->cmd_line = get_commands(av);
		set_opts(commands);
		printf("opt 1 = %d, next_opt = %d\n", commands->opt, commands->next_opt);
		printf("cmd 1 = %s\n", commands->cmd_line[0][0]);
	}
	return (0);
	
}
