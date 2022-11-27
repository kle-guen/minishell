/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:38:55 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/27 13:52:48 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_no_quotes_no_dollar(char *input, int *index, int *index_str)
{
	int		i;
	char 	*str;

	i = 0;
	if (input[i] != '$')
		str = malloc(sizeof(char) * (ft_strlen_noquote(input) + 1));
	else
		str = ft_calloc(1, sizeof(char));
	while (input[i] != '$' && input[i] != '|' && input[i] != '<' && input[i] != '>' && input[i])
	{
		if ((input[i] == 39 && ft_is_close_quotes(input + i + 1, 39)) || (input[i] == '"' && ft_is_close_quotes(input + i + 1, '"')))
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
				str = ft_remove_double_quotes_closed(input, index, env_list);
			else
				str = ft_remove_double_quotes_unclosed(input, index);
		}
	}
	else
	{
		if (ft_is_close_quotes(input + 1, '"'))
			str = ft_remove_double_quotes_closed(input, index, env_list);
		else
			str = ft_remove_double_quotes_unclosed(input, index);
	}
	return (str);
}

void	ft_redir_and_pipe(char *input, char **clean_input, int *index)
{
	int i;
	int	len_redir;

	i = *index;
	len_redir = 0;
	if (input[i] == '|' || (input[i] == '<' && input[i + 1] != '<') || (input[i] == '>' && input[i + 1] != '>'))
	{
		if (i && input[i + 1] && ((input[i - 1] == 39 && input[i + 1] == 39) || (input[i - 1] == '"' && input[i + 1] == '"')))
		{
			*clean_input = ft_strjoin_sep(*clean_input, ft_substr(input, i - 1, 3));
			*index += 2;
		}
		else
		{
			*clean_input = ft_strjoin_sep(*clean_input, ft_substr(input, i, 1));
			(*index)++;
		}
	}
	else
	{
		len_redir = ft_strlen_redir(input + i, input[i]);
		if (i && input[i + 1] && ((input[i - 1] == 39 && input[i + len_redir] == 39) || (input[i - 1] == '"' && input[i + len_redir] == '"')))
		{
			*clean_input = ft_strjoin_sep(*clean_input, ft_substr(input, i - 1, len_redir + 2));
			*index += len_redir + 1;
		}
		else
		{
			*clean_input = ft_strjoin_sep(*clean_input, ft_substr(input, i, len_redir));
			*index += len_redir;
		}
	}
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
		if (input[i] == 39 && input[i])
		{
			if (i)
				clean_input = ft_strjoin_dfree(clean_input, ft_single_quotes(input + i, &i, input[i - 1]));
			else
				clean_input = ft_strjoin_dfree(clean_input, ft_single_quotes(input + i, &i, 0));
		}
		if (input[i] == '"' && input[i])
		{
			if (i)
				clean_input = ft_strjoin_dfree(clean_input, ft_double_quotes(input + i, env_list, &i, input[i - 1]));
			else
				clean_input = ft_strjoin_dfree(clean_input, ft_double_quotes(input + i, env_list, &i, 0));
		}
		if ((input[i] == '|' || input[i] == '<' || input[i] == '>')  && input[i])
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

/*
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
			clean_input = ft_strjoin_dfree(clean_input, ft_no_quotes(input + i, env_list, &i));
		if (input[i] == 39 && input[i])
		{
			if (i)
				clean_input = ft_strjoin_dfree(clean_input, ft_single_quotes(input + i, &i, input[i - 1]));
			else
				clean_input = ft_strjoin_dfree(clean_input, ft_single_quotes(input + i, &i, 0));
		}
		if (input[i] == '"' && input[i])
		{
			if (i)
				clean_input = ft_strjoin_dfree(clean_input, ft_double_quotes(input + i, env_list, &i, input[i - 1]));
			else
				clean_input = ft_strjoin_dfree(clean_input, ft_double_quotes(input + i, env_list, &i, 0));
		}
		if ((input[i] == '|' || input[i] == '<' || input[i] == '>')  && input[i])
		{
			clean_input = ft_strjoin_sep(clean_input, NULL);
			if (input[i] == '|' || (input[i] == '<' && input[i + 1] != '<') || (input[i] == '>' && input[i + 1] != '>'))
			{
				if (i && input[i + 1] && ((input[i - 1] == 39 && input[i + 1] == 39) || (input[i - 1] == '"' && input[i + 1] == '"')))
				{
					clean_input = ft_strjoin_sep(clean_input, ft_substr(input, i - 1, 3));
					i += 2;
				}
				else
				{		
					clean_input = ft_strjoin_sep(clean_input, ft_substr(input, i, 1));
					i++;
				}
			}
			else
			{
				len_redir = ft_strlen_redir(input + i, input[i]);
				if (i && input[i + 1] && ((input[i - 1] == 39 && input[i + len_redir] == 39) || (input[i - 1] == '"' && input[i + len_redir] == '"')))
				{
					clean_input = ft_strjoin_sep(clean_input, ft_substr(input, i - 1, len_redir + 2));
					i += len_redir + 1;
				}
				else
				{	
					clean_input = ft_strjoin_sep(clean_input, ft_substr(input, i, len_redir));
					i += len_redir;
				}
			}
		}
	}
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
	i = 0;
	while (cmd_args[i])
	{
		if (cmd_args[i][0] == -2)
			cmd_args[i][0] = '\0';
		i++;
	}
	return (cmd_args);
}
*/