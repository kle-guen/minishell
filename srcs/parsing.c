/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:38:55 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/28 14:36:38 by kle-guen         ###   ########.fr       */
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
			str = ft_strjoin_dfree(str, ft_replace_dollar(input + i + 1, env_list, index, NULL));
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
		if (prev == ' ' && input[1] == 39 && (input[2] == ' ' || input[2] == '\0'))
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
		if (prev == ' ' && input[1] == 39 && (input[2] == ' ' || input[2] == '\0'))
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

char	*ft_clean_input(char *input, t_env *env_list)
{
	int		i;
	char	*clean_input;

	i = 0;
	clean_input = ft_calloc(1, sizeof(char));
	while (input[i])
	{
		if (input[i] != '"' && input[i] != 39)
			clean_input = ft_strjoin_dfree(clean_input, ft_no_quotes(input + i, env_list, &i));
		if (input[i] == 39 && input[i] && i)
			clean_input = ft_strjoin_dfree(clean_input, ft_single_quotes(input + i, &i, input[i - 1]));
		if (input[i] == 39 && input[i] && !i)
			clean_input = ft_strjoin_dfree(clean_input, ft_single_quotes(input + i, &i, 0));
		if (input[i] == '"' && input[i] && i)
			clean_input = ft_strjoin_dfree(clean_input, ft_double_quotes(input + i, env_list, &i, input[i - 1]));
		if (input[i] == '"' && input[i] && !i)
			clean_input = ft_strjoin_dfree(clean_input, ft_double_quotes(input + i, env_list, &i, 0));
		if (ft_strchr("|><", input[i]) && input[i])
		{
			clean_input = ft_strjoin_sep(clean_input, NULL);
			ft_redir_and_pipe(input, &clean_input, &i);
		}
	}
	return (clean_input);
}

char	**ft_parse_input(char *input, t_env *env_list)
{
	int		i;
	char	*clean_input;
	char	**cmd_args;

	i = 0;
	clean_input = ft_clean_input(input, env_list);
	if ((!ft_strncmp(input, "\"\"", 3)) || (!(ft_strncmp(input, "\'\'", 3))))
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
	while (cmd_args[i])
	{
		if (cmd_args[i][0] == -2)
			cmd_args[i][0] = '\0';
		i++;
	}
	return (cmd_args);
}
