/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils_5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:29:01 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/30 12:29:31 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_env(t_env *env_list)
{
	t_env	*tmp;

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

void	ft_find_next_to_print(t_env **env_list, t_env **tmp)
{
	int		len1;
	int		len2;

	*tmp = *env_list;
	*env_list = (*env_list)->next;
	while (*env_list)
	{
		len1 = ft_strlen((*tmp)->key);
		len2 = ft_strlen((*env_list)->key);
		if (len1 > len2)
		{
			if (strncmp((*tmp)->key, (*env_list)->key, len2 + 1) > 0 && \
			!((*env_list)->is_printed))
				*tmp = *env_list;
		}
		else
		{
			if (strncmp((*env_list)->key, (*tmp)->key, len1 + 1) < 0 && \
			!((*env_list)->is_printed))
				*tmp = *env_list;
		}
		*env_list = (*env_list)->next;
	}
}

void	ft_print_export(t_env *env_list)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = env_list;
	ft_set_is_printed(env_list);
	while (env_list)
	{	
		ft_find_next_to_print(&env_list, &tmp2);
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
