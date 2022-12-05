/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:05:56 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/05 15:29:41 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_double_char(char *str)
{	
	int	index;

	index = 1;
	if ((str[index - 1] == '>' && str[index]))
	{
		if (str[index] == '>' && str[index])
			index++;
		if (str[index] == '\0')
			return (1);
	}
	else if ((str[index - 1] == '<' && str[index]))
	{
		if (str[index] == '<' && str[index])
			index++;
		if (str[index] == '\0')
			return (1);
	}
	return (0);
}

int	is_pipe(const char *str)
{
	int	x;

	x = 0;
	if (str == NULL)
		return (0);
	while (str[x] != '\0')
	{
		if (str[0] == '|' && str[1] == '\0')
			return (1);
		x++;
	}
	return (0);
}

int	what_separator(const char *separator)
{
	int	symbol;
	int	x;

	x = 0;
	symbol = 0;
	if (separator == NULL)
		return (-1);
	else if (separator[x] == '<' && separator[x + 1] == '\0')
		symbol = 1;
	else if (separator[x] == '>' && separator[x + 1] == '\0')
		symbol = 2;
	else if (separator[x] == '<')
		symbol = 3;
	else if (separator[x] == '>')
		symbol = 4;
	return (symbol);
}

int	is_separator(char *str)
{
	int	is_separator;
	int	x;

	x = 0;
	is_separator = 0;
	if (str == NULL)
		return (is_separator);
	if (str[x] == '\0')
		return (is_separator);
	if (str[x] == '>' || str[x] == '<')
	{
		x++;
		if (str[x] == '\0')
			return (1);
	}
	is_separator = is_double_char(str);
	return (is_separator);
}
