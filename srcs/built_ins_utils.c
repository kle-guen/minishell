/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 15:42:13 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/15 18:39:00 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_get_cwd(void)
{
	char	*buff;
	size_t		i;

	i = 0;
	buff = malloc(sizeof(char));
	while (getcwd(buff, i) == NULL && i < UINT_MAX)
	{
		free(buff);
		buff = malloc(sizeof(char) + i * sizeof(char));
		i++;
	}
	return (buff);
}


char	*ft_get_env(char *key, t_env *env_list)
{
	t_env	*tmp;
	int		len_key;
	char	*value;

	value = NULL;
	len_key = ft_strlen(key);
	tmp = env_list;
	while (env_list)
	{
		if (!(strncmp(key, env_list->key, len_key)))
		{
			value = env_list->value;
			break ;
		}
		env_list = env_list->next;
	}
	env_list = tmp;
	return (value);
}

int	ft_key_has_value(char *new_env)
{
	int	i;

	i = 0;
	while (new_env[i])
	{
		if (new_env[i] == '=')
		{
			return (2);
		}
		else if (new_env[i] == '+' && new_env[i + 1] == '=')
		{
			return (3);
		}
		else if ((new_env[i] == '+' && new_env[i + 1] != '=') || (!(ft_isalnum(new_env[i]))))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_join_key_value(t_env *env_list, char *key, char *value)
{
	t_env	*tmp;
	int		len_key;
	
	len_key = ft_strlen(key);
	tmp = env_list;
	while (env_list)
	{
		if (!(strncmp(env_list->key, key, len_key)) && (int)ft_strlen(env_list->key) == len_key)
			break;
		env_list = env_list->next;
	}
	if (!env_list->value)
		env_list->value = ft_calloc(1, sizeof(char));
	env_list->value = ft_strjoin_dfree(env_list->value, value);
	env_list = tmp;
}

void	ft_remove_plus(char *arg)
{
	char	*cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cpy = ft_strdup(arg);
	free(arg);
	arg = malloc(sizeof(char) * ft_strlen(cpy));
	while (cpy[i])
	{
		if (cpy[i] != '+')
		{
			arg[j] = cpy[i];
			j++;
		}
		i++;

	}
	arg[j] = '\0';
}