/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_after_parsing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 15:47:15 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/01 11:52:20 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../../includes/minishell.h"

int	check_unclosed_quotes(char **input)
{
	while (*input != NULL)
	{
		if (is_unclosed(*input) == 0)
			return (0);
		input++;
	}
	return (1);
}

int	check_next_str(char **input)
{
	input++;
	if (is_separator(*input) || is_pipe(*input) || *input == NULL)
		return (0);
	return (1);
}

int	multiple_symbole(char *str)
{
	int	x;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] != '\0' && str[x] == '>')
		{
			x++;
			if (str[x] != '\0' && str[x] == '>')
			{
				x++;
				if (str[x] != '\0' && (str[x] == '>' || str[x] == '<'))
					return (0);
			}
		}
		x++;
	}
	return (1);
}

int	check_multiple_symbole(char **input)
{
	while (*input != NULL)
	{
		if (multiple_symbole(*input) == 0)
			return (0);
		input++;
	}
	return (1);
}

int	check_after_parsing(char **input)
{
	if (is_pipe(*input))
		return (0);
	if (check_unclosed_quotes(input) == 0)
		return (0);
	while (*input != NULL)
	{
		if (is_separator(*input))
		{
			if (check_next_str(input) == 0)
				return (0);
			input++;
		}
		else if (is_pipe(*input))
		{
			input++;
			if (is_pipe(*input))
				return (0);
		}
		input++;
	}
	input--;
	if (is_pipe(*input))
		return (0);
	return (1);
}
