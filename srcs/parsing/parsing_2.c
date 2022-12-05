/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:23:58 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/30 12:24:40 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_no_quotes(char *input, t_env *env_list, int *index)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_no_quotes_no_dollar(input, index, &i);
	if (input[i] == '$')
	{
		if (input[i + 1])
			str = ft_strjoin_dfree(str, \
			ft_replace_dollar(input + i + 1, env_list, index, NULL));
		else
		{
			str[i++] = '$';
			str[i] = '\0';
			(*index)++;
		}
	}
	return (str);
}

char	*ft_single_quotes(char *input, int *index, char prev)
{
	char	*str;

	if (input[1] == '>' || input[1] == '<' || input[1] == '|')
		str = ft_keep_quotes(input, index, 39);
	else if (ft_strlen(input) > 1 && prev)
	{
		if (prev == ' ' && input[1] == 39 && \
		(input[2] == ' ' || input[2] == '\0'))
			str = ft_empty_string(index);
		else
			str = ft_remove_single_quotes(input, index);
	}
	else
		str = ft_remove_single_quotes(input, index);
	return (str);
}

char	*ft_double_quotes(char *input, t_env *env_list, int *index, char prev)
{
	char	*str;

	if (input[1] == '>' || input[1] == '<' || input[1] == '|')
		str = ft_keep_quotes(input, index, '"');
	else if (ft_strlen(input) > 1 && prev)
	{
		if (prev == ' ' && input[1] == 39 && \
		(input[2] == ' ' || input[2] == '\0'))
			str = ft_empty_string(index);
		else
		{	
			if (ft_is_close_quotes(input + 1, '"'))
				str = ft_double_quotes_closed(input, index, env_list);
			else
				str = ft_double_quotes_unclosed(input, index);
		}
	}
	else
	{
		if (ft_is_close_quotes(input + 1, '"'))
			str = ft_double_quotes_closed(input, index, env_list);
		else
			str = ft_double_quotes_unclosed(input, index);
	}
	return (str);
}
