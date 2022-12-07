/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 08:14:03 by kle-guen          #+#    #+#             */
/*   Updated: 2022/12/07 13:47:12 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_keep_quotes(char *input, int *index, char quote)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen_quote(input + 1, quote) + 3));
	if (!str)
		return (NULL);
	while (input[i + 1] != quote)
	{
		str[i] = input[i];
		i++;
	}
	str[i] = input[i];
	str[++i] = quote;
	str[++i] = '\0';
	*index += ft_strlen_quote(input + 1, quote) + 2;
	return (str);
}

char	*ft_empty_string(int *index)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	if (!str)
		return (NULL);
	str[0] = -2;
	*index += 2;
	return (str);
}

char	*ft_remove_single_quotes(char *input, int *index)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_calloc((ft_strlen_quote(input + 1, 39) + 1), sizeof(char));
	if (str && ft_is_close_quotes(input + 1, 39))
	{
		while (input[i + 1] != 39)
		{
			str[i] = input[i + 1];
			i++;
		}
		*index += i + 2;
	}
	else if (str)
	{
		while (input[i] && !ft_strchr(" \"|><$", input[i]))
		{
			str[i] = input[i];
			i++;
		}
		*index += i;
	}
	return (str);
}

char	*ft_double_quotes_closed(char *input, int *index, t_env *env_list)
{
	int		i;
	int		y;
	int		len;
	char	*str;

	y = 0;
	i = 1;
	len = ft_strlen_quote(input + 1, '"');
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (input[i] && input[i] != '"')
	{
		if (input[i] == '$' && input[i + 1] != '"' && input[i + 1] != ' ')
		{
			str[y] = '\0';
			str = ft_realloc_key(str, \
			ft_replace_dollar(input + i + 1, env_list, &i, &len), &len, &y);
		}
		else
			str[y++] = input[i++];
	}
	*index += i + 1;
	return (str);
}

char	*ft_double_quotes_unclosed(char *input, int *index)
{
	int		i;
	int		y;
	char	*str;

	i = 1;
	y = 0;
	str = malloc(sizeof(char) * (ft_strlen_quote(input + 1, '"') + 1));
	if (!str)
		return (NULL);
	while (input[i] && !ft_strchr(" '|><$", input[i]))
	{
		str[y] = input[i];
		i++;
		y++;
	}
	str[y] = '\0';
	*index += i;
	return (str);
}
