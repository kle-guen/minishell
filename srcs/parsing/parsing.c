/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 10:38:55 by kle-guen          #+#    #+#             */
/*   Updated: 2022/12/07 13:17:35 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*launch_dquotes(char *str, char *input, int *index, t_env *env_list)
{
	char	*new_str;
	char	*str_parsed;
	int		i;

	i = *index;
	if (i)
		str_parsed = ft_double_quotes(input + i, env_list, index, input[i - 1]);
	else
		str_parsed = ft_double_quotes(input + i, env_list, index, 0);
	new_str = ft_strjoin_dfree(str, str_parsed);
	return (new_str);
}

char	*launch_squotes(char *str, char *input, int *index)
{
	char	*new_str;
	char	*str_parsed;
	int		i;

	i = *index;
	if (i)
		str_parsed = ft_single_quotes(input + i, index, input[i - 1]);
	else
		str_parsed = ft_single_quotes(input + i, index, 0);
	new_str = ft_strjoin_dfree(str, str_parsed);
	return (new_str);
}

char	*launch_no_quotes(char *str, char *input, int *index, t_env *env_list)
{
	char	*new_str;
	char	*str_parsed;
	int		i;

	i = *index;
	str_parsed = ft_no_quotes(input + i, env_list, index);
	new_str = ft_strjoin_dfree(str, str_parsed);
	return (new_str);
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
			clean_input = launch_no_quotes(clean_input, input, &i, env_list);
		if (input[i] == 39 && input[i])
			clean_input = launch_squotes(clean_input, input, &i);
		if (input[i] == '"' && input[i])
			clean_input = launch_dquotes(clean_input, input, &i, env_list);
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
		if (!cmd_args)
			return (NULL);
		cmd_args[0] = ft_strdup("''");
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
