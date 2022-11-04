/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:38:55 by kle-guen          #+#    #+#             */
/*   Updated: 2022/10/29 11:45:06 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_no_quotes(char *input, t_env *env_list, int *index)
{
	char	*str;
	int		i;

	i = 0;
	if (input[i] != '$')
		str = malloc(sizeof(char) * (ft_strlen_noquote(input) + 1));
	else
		str = ft_calloc(1, sizeof(char));
	while (input[i] != '$' && input[i] != '|' && input[i] != '<' && input[i] != '>' && input[i])
	{
		if ((input[i] == 39 && ft_is_close_quotes(input + i + 1, 39)) || (input[i] == '"' && ft_is_close_quotes(input + i + 1, '"')))
			break ;
		if (input[i] == ' ')
			str[i] = -1;
		else
			str[i] = input[i];
		i++;
	}
	str[i] = '\0';
	*index += i;
	if (input[i] == '$')
		str = ft_strjoin(str, ft_replace_dollar(input + i + 1, env_list, index, NULL));
	return (str);
}

char	*ft_single_quotes(char *input, int *index)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc(sizeof(char) * (ft_strlen_quote(input + 1, 39) + 1));
	if (ft_is_close_quotes(input + 1, 39))
	{
		while (input[i + 1] != 39)
		{
			str[i] = input[i + 1];
			i++;
		}
		*index += i + 2;
	}
	else
	{
		while (input[i] && input[i] != ' ' && input[i] != '"' && input[i] != '|' && input[i] != '>' && input[i] != '<' && input[i] != '$')
		{
			str[i] = input[i];
			i++;
		}
		*index += i;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_double_quotes(char *input, t_env *env_list, int *index)
{
	char	*str;
	int		len;
	int		i;
	int		y;

	y = 0;
	i = 1;
	len = ft_strlen_quote(input + 1, '"');
	str = malloc(sizeof(char) * (len + 1));
	if (ft_is_close_quotes(input + 1, '"'))
	{
		while (input[i] && input[i] != '"')
		{
			if (input[i] == '$')
			{
				str[y] = '\0';
				str = ft_realloc_key(str, ft_replace_dollar(input + i + 1, env_list, &i, &len), &len, &y);
			}
			else
			{	
				str[y] = input[i];
				i++;
				y++;
			}
		}
		str[y] = '\0';
		*index += i + 1;
	}
	else
	{
		i = 0;
		while (input[i] && input[i] != ' ' && input[i] != 39 && input[i] != '|' && input[i] != '>' && input[i] != '<' && input[i] != '$')
		{
			str[y] = input[i];
			i++;
			y++;
		}
		str[y] = '\0';
		*index += i;
	}
	return (str);
}

char	**ft_parse_input(char *input, t_env *env_list)
{
	int		i;
	char	*clean_input;
	char	**cmd_args;
	int		len_redir;

	i = 0;
	clean_input = ft_calloc(1, sizeof(char));
	while (input[i])
	{
		if (input[i] != '"' && input[i] != 39)
			clean_input = ft_strjoin(clean_input, ft_no_quotes(input + i, env_list, &i));
		if (input[i] == 39 && input[i])
			clean_input = ft_strjoin(clean_input, ft_single_quotes(input + i, &i));
		if (input[i] == '"' && input[i])
			clean_input = ft_strjoin(clean_input, ft_double_quotes(input + i, env_list, &i));
		if ((input[i] == '|' || input[i] == '<' || input[i] == '>')  && input[i])
		{
			clean_input = ft_strjoin_sep(clean_input, NULL);
			if (input[i] == '|' || (input[i] == '<' && input[i + 1] != '<') || (input[i] == '>' && input[i + 1] != '>'))
			{
				clean_input = ft_strjoin_sep(clean_input, ft_substr(input, i, 1));
				i++;
			}
			else
			{
				len_redir = ft_strlen_redir(input + i, input[i]);
				clean_input = ft_strjoin_sep(clean_input, ft_substr(input, i, len_redir));
				i += len_redir;
			}
		}
	}
	if (!clean_input[0] && (ft_is_close_quotes(input + 1, 39) || ft_is_close_quotes(input + 1, '"')))
	{
		cmd_args = malloc(sizeof(char *) * 2);
		cmd_args[0] = malloc(sizeof(char) * 3);
		cmd_args[0][0] = 39;
		cmd_args[0][1] = 39;
		cmd_args[0][2] = '\0';
		cmd_args[1] = NULL;
	}
	else
		cmd_args = ft_split(clean_input, -1);
	free(clean_input);
	i = 0;
	//while (cmd_args[i])
	//	printf("%s\n", cmd_args[i++]);
	return (cmd_args);
}
