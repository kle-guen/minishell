/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:08:54 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/28 16:35:02 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*ft_laststack(t_env *env_list)
{
	if (env_list)
	{
		while (env_list->next)
			env_list = env_list->next;
	}
	return (env_list);
}

t_env	*ft_new_lst_env(char *arg)
{
	t_env	*elem;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->key = ft_get_key(arg);
	elem->value = ft_get_value(arg);
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

t_env	*ft_create_env_list(char **envp)
{
	t_env	*env_list;
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
