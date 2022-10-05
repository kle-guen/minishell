/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:38:55 by kle-guen          #+#    #+#             */
/*   Updated: 2022/10/05 15:24:03 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_close_quotes(char *str, char quote)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == quote)
			return (1);
		i++;
	}
	return (0);
}

int	ft_count_quotes(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while(str[i])
	{
		if (str[i] == 39 || str[i] == '"')
			count++;
		i++;
	}
	return (count);
}

void	ft_single_quotes(char *clean_input, char *input, int *i, int *j)
{
	int	k;

	k = *i + 1;
	if (ft_is_close_quotes(input + *i + 1, 39))
	{
		while (input[k++] != 39)
		{
			clean_input[(*j)++] = input[(*i)++ + 1];
		}
		*i = k;
	}
	else
	{
		while (input[*i] != '\0')
		{
			clean_input[(*j)++] = input[(*i)++];
		}
	}
}

void	ft_double_quotes(char *clean_input, char *input, int *i, int *j)
{
	int	k;

	k = *i + 1;
	if (ft_is_close_quotes(input + *i + 1, '"'))
	{
		while (input[k++] != '"')
		{
			clean_input[(*j)++] = input[(*i)++ + 1];
		}
		*i = k;
	}
	else
	{
		while (input[*i] != '\0')
		{
			clean_input[(*j)++] = input[(*i)++];
		}
	}
}

char	*ft_parse_input(char *input)
{
	int		i;
	int		j;
	char	*clean_input;

	i = 0;
	j = 0;
	clean_input = malloc(sizeof(char) * (ft_strlen(input) + 1));
	while (input[i])
	{
		while (input[i] != '"' && input[i] != 39 && input[i])
		{
			clean_input[j++] = input[i++];
		}
		if (input[i] == 39 && input[i])
		{
			ft_single_quotes(clean_input, input, &i, &j);
			if (!(input[i]))
				break ;
		}
		else if (input[i] == '"' && input[i])
		{	
			ft_double_quotes(clean_input, input, &i, &j);
			if (!(input[i]))
				break ;
		}
	}
	clean_input[j] = '\0';
	return (clean_input);
}
