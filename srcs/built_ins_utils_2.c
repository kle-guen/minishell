/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:39:31 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/28 13:52:57 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_plus_equal_export(t_env *env_list, char *arg)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	key = malloc(sizeof(char) * (ft_strlen_key_plus(arg) + 1));
	value = ft_get_value(arg);
	while (arg[i] != '+')
	{
		key[i] = arg[i];
		i++;
	}
	key[i] = '\0';
	if (ft_key_is_in_env(env_list, key))
	{
		ft_join_key_value(env_list, key, value);
	}
	else
	{
		ft_remove_plus(arg);
		ft_add_back_lst_env(&env_list, ft_new_lst_env(arg));
	}
}

void	ft_replace_env_value(t_env *env_list, char *key, char *value)
{
	t_env	*tmp;
	int		len_key;

	len_key = ft_strlen(key);
	tmp = env_list;
	while (env_list)
	{
		if (!(strncmp(env_list->key, key, len_key)) && \
		(int)ft_strlen(env_list->key) == len_key)
			break ;
		env_list = env_list->next;
	}
	free(env_list->value);
	env_list->value = value;
	env_list = tmp;
	free(key);
}

void	ft_add_env(t_env *env_list, char *arg)
{
	if (ft_key_has_value(arg) == 1)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		g_exit_status = 1;
	}
	else if (ft_key_has_value(arg) == 2)
	{
		if (!(ft_key_is_in_env(env_list, ft_get_key(arg))))
			ft_add_back_lst_env(&env_list, ft_new_lst_env(arg));
		else
			ft_replace_env_value(env_list, ft_get_key(arg), ft_get_value(arg));
	}
	else if (ft_key_has_value(arg) == 3)
		ft_plus_equal_export(env_list, arg);
	else
		if (!(ft_key_is_in_env(env_list, ft_get_key(arg))))
			ft_add_back_lst_env(&env_list, ft_new_lst_env(arg));
}

void	ft_remove_first_env_var(t_env **env_list)
{
	t_env	*tmp;

	tmp = *env_list;
	*env_list = (*env_list)->next;
	ft_free_env_var(tmp);
}

void	ft_remove_env(t_env **env_list, char *arg, int len_key, t_env *tmp)
{
	t_env	*tmp2;

	if (!(strncmp((*env_list)->key, arg, len_key)) && \
	(int)ft_strlen((*env_list)->key) == len_key)
	{
		ft_remove_first_env_var(env_list);
		return ;
	}
	else
	{
		while ((*env_list)->next)
		{
			if (!(strncmp((*env_list)->next->key, arg, len_key)) && \
			(int)ft_strlen((*env_list)->next->key) == len_key)
			{
				tmp2 = (*env_list)->next;
				(*env_list)->next = tmp2->next;
				ft_free_env_var(tmp2);
				break ;
			}
			*env_list = (*env_list)->next;
		}
	}
	*env_list = tmp;
}
