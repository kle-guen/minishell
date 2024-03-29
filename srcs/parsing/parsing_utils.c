/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:11:14 by kle-guen          #+#    #+#             */
/*   Updated: 2022/12/07 18:57:30 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_delete_wrong_key(char **key)
{
	free((*key));
	(*key) = ft_calloc(1, sizeof(char));
}

void	ft_match_key(char **key, int len, t_env *env_list)
{
	t_env			*tmp;
	unsigned char	exit_status;

	exit_status = g_exit_status;
	if (!(strncmp((*key), "?", 1)))
	{
		free((*key));
		(*key) = ft_itoa(exit_status);
		return ;
	}
	tmp = env_list;
	while (env_list)
	{
		if (len == (int)ft_strlen(env_list->key) && \
		!(strncmp((*key), env_list->key, len)) && (env_list->value))
		{
			free((*key));
			(*key) = ft_strdup(env_list->value);
			break ;
		}
		env_list = env_list->next;
	}
	if (!env_list)
		ft_delete_wrong_key(key);
	env_list = tmp;
}

char	*ft_replace_dollar(char *input, t_env *env_list, int *index, int *len)
{
	char	*key;
	int		i;
	int		len_key;

	i = 0;
	len_key = ft_strlen_dollar(input);
	key = malloc(sizeof(char) * (len_key + 1));
	if (!key)
		return (NULL);
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

void	ft_fill_new_str(char *str, char *key, char *new_str, int *index)
{
	int	len_key;
	int	i;
	int	j;

	i = 0;
	j = 0;
	len_key = ft_strlen(key);
	while (str[i])
	{
		new_str[i] = str[i];
		i++;
	}
	while (j < len_key)
	{
		new_str[i] = key[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	*index = i;
}

char	*ft_realloc_key(char *str, char *key, int *len, int *index)
{
	int		new_len;
	char	*new_str;

	new_len = *len + ft_strlen(str) + ft_strlen(key);
	new_str = ft_calloc(new_len + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	ft_fill_new_str(str, key, new_str, index);
	free(str);
	free(key);
	return (new_str);
}
