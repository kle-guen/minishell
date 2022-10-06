/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:59:08 by kle-guen          #+#    #+#             */
/*   Updated: 2022/10/06 12:08:41 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen_key(char *str)
{
	int i;

	i = 0;
	while (str[i] != '=')
		i++;
	return (i);
}

char	*ft_get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	key = malloc(sizeof(char) * (ft_strlen_key(str) + 1));
	while (str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	return (key);
}

char	*ft_get_value(char *str)
{
	int		i;
	int		len_key;
	char	*value;

	i = 0;
	len_key = ft_strlen_key(str);
	value = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen_key(str) + 1));
	while (str[len_key + i + 1])
	{
		value[i] = str[len_key + i + 1];
		i++;
	}
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

void	ft_print_list(t_env *env_list)
{
	t_env *tmp;

	tmp = env_list;
	while (env_list)
	{
		printf("%s=%s\n", (env_list)->key, (env_list)->value);
		(env_list) = (env_list)->next;
	}
	env_list = tmp;

}

t_env	*ft_laststack(t_env *env_list)
{
	if (env_list)
	{
		while (env_list->next)
			env_list = env_list->next;
	}
	return (env_list);
}

t_env	*ft_new_lst_env(char *envp)
{
	t_env	*elem;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->key = ft_get_key(envp);
	elem->value = ft_get_value(envp);
	elem->next = NULL; 
	return (elem);
}

t_env	*ft_last_lst_env(t_env *env_list)
{
	if (env_list)
	{
		while (env_list->next)
			env_list = env_list->next;
	}
	return (env_list);
}

void	ft_add_back_lst_env(t_env **env_list, t_env *new)
{
	t_env	*tmp;

	if (*env_list)
	{
		tmp = ft_laststack(*env_list);
		tmp->next = new;
	}
	else
		*env_list = new;
}

t_env   *ft_create_env_list(char **envp)
{
    t_env   *env_list;
	int		i;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		ft_add_back_lst_env(&env_list, ft_new_lst_env(envp[i]));
		i++;
	}
	return (env_list);
}
