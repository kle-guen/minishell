/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:59:08 by kle-guen          #+#    #+#             */
/*   Updated: 2022/10/31 14:00:47 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin_sep(char *s1, char *s2)
{
	int		i;
	size_t	len1;
	size_t	len2;
	char	*str;

	if (!s2)
		s2 = ft_calloc(1, sizeof(char));
	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!str)
		return (NULL);
	while (s1[i])
	{	
		str[i] = s1[i];
		i++;
	}
	while (s2[i - len1])
	{
		str[i] = s2[i - len1];
		i++;
	}
	str[i] = -1;
	str[i + 1] = '\0';
	free(s1);
	free(s2);
	return (str);
}

char	*ft_get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	key = malloc(sizeof(char) * (ft_strlen_key(str) + 1));
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*ft_get_value(char *str)
{
	int		i;
	int		len_key;
	char	*value;

	if (!(ft_strchr(str, '=')))
		return (NULL);
	i = 0;
	len_key = ft_strlen_key(str);
	value = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen_key(str) + 1));
	while (str[len_key + i + 1])
	{
		value[i] = str[len_key + i + 1];
		i++;
	}
	value[i] = '\0';
	return (value);
}

int	ft_strrlen(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_print_env(t_env *env_list)
{
	t_env *tmp;

	tmp = env_list;
	while (env_list)
	{
		if (env_list->value)
			printf("%s=%s\n", (env_list)->key, (env_list)->value);
		(env_list) = (env_list)->next;
	}
	env_list = tmp;
}
void	ft_set_is_printed(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (env_list)
	{
		env_list->is_printed = 0;
		env_list = env_list->next;
	}
	env_list = tmp;
}

void	ft_print_export(t_env *env_list)
{
	t_env	*tmp;
	t_env	*tmp2;
	int		len1;
	int 	len2;

	tmp = env_list;
	ft_set_is_printed(env_list);
	while (env_list)
	{
		tmp2 = env_list;
		env_list = env_list->next;
		while (env_list)
		{
			len1 = ft_strlen(tmp2->key);
			len2 = ft_strlen(env_list->key);
			if (len1 > len2)
			{
				if (strncmp(tmp2->key, env_list->key, len2 + 1) > 0 && !(env_list->is_printed))
					tmp2 = env_list;
			}
			else
			{
				if (strncmp(env_list->key, tmp2->key, len1 + 1) < 0 && !(env_list->is_printed))
					tmp2 = env_list;
			}
			env_list = env_list->next;
		}
		if (strncmp(tmp2->key, "_", 1) || ft_strlen(tmp2->key) != 1)
		{	
			if (tmp2->value)
				printf("declare -x %s=\"%s\"\n", tmp2->key, tmp2->value);
			else
				printf("declare -x %s\n", tmp2->key);
		}
		tmp2->is_printed = 1;
		env_list = tmp;
		while (env_list->is_printed)
		{
			env_list = env_list->next;
			if (!(env_list))
				break ;
		}
	}
	env_list = tmp;
}
