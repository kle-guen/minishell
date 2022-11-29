/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:36:30 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/28 14:26:41 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_close_quotes(char *str, char quote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == quote)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_no_quotes_no_dollar(char *input, int *index, int *index_str)
{
	int		i;
	char	*str;

	i = 0;
	if (input[i] != '$')
		str = malloc(sizeof(char) * (ft_strlen_noquote(input) + 1));
	else
		str = ft_calloc(1, sizeof(char));
	while (!ft_strchr("$|<>", input[i]) && input[i])
	{
		if ((input[i] == 39 && ft_is_close_quotes(input + i + 1, 39)) || \
		(input[i] == '"' && ft_is_close_quotes(input + i + 1, '"')))
			break ;
		if (input[i] == ' ' || input[i] == '\t')
			str[i] = -1;
		else
			str[i] = input[i];
		i++;
	}
	str[i] = '\0';
	*index += i;
	*index_str = i;
	return (str);
}

void	ft_redir_and_pipe(char *input, char **clean_input, int *index)
{
	int		i;
	int		len_redir;
	char	*str;

	i = *index;
	len_redir = 0;
	if (input[i] == '|' || (input[i] == '<' && input[i + 1] != '<') \
	|| (input[i] == '>' && input[i + 1] != '>'))
	{
		str = ft_substr(input, i, 1);
		*clean_input = ft_strjoin_sep(*clean_input, str);
		(*index)++;
	}
	else
	{
		len_redir = ft_strlen_redir(input + i, input[i]);
		str = ft_substr(input, i, len_redir);
		*clean_input = ft_strjoin_sep(*clean_input, str);
		*index += len_redir;
	}
}
