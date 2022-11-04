/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:11:14 by kle-guen          #+#    #+#             */
/*   Updated: 2022/10/28 11:35:06 by kle-guen         ###   ########.fr       */
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

void	ft_match_key(char **key, int len, t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (env_list)
	{
		if (len == (int)ft_strlen(env_list->key) && !(strncmp((*key), env_list->key, len)))
		{
			free((*key));
			(*key) = ft_strdup(env_list->value);
			break ;
		}
		env_list = env_list->next;
	}
	if (!env_list)
	{
		free((*key));
		(*key) = ft_calloc(1, sizeof(char));
	}
	env_list = tmp;
}

char	*ft_replace_dollar(char *input, t_env *env_list , int *index, int *len)
{
	char	*key;
	int		i;
	int		len_key;

	i = 0;
	len_key = ft_strlen_dollar(input);
	key = malloc(sizeof(char) * (len_key + 1));
	while (i < len_key)
	{
		key[i] = input[i];
		i++;
	}
	key[i] = '\0';
	ft_match_key(&key, len_key, env_list);
	if (len)
		*len -= len_key;
	if (index)
		*index += len_key + 1;
	return (key);
}

void	ft_fill_new_str(char *str, char *key, char *new_str, int *i)
{
	int	len_key;
	int	j;

	j = 0;	
	len_key = ft_strlen(key);
	while (str[*i])
	{
		new_str[*i] = str[*i];
		(*i)++;
	}
	while (j < len_key)
	{
		new_str[*i] = key[j];
		(*i)++;
		j++;
	}
	new_str[*i] = '\0';
}

char	*ft_realloc_key(char *str, char *key, int *len, int *index)
{
	int		i;
	int		new_len;
	char	*new_str;

	i = 0;
	new_len = *len + ft_strlen(key);
	new_str = malloc(sizeof(char) * new_len);
	ft_fill_new_str(str, key, new_str, &i);
	*index = i;
	free(str);
	free(key);
	return (new_str);
}