/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:41:27 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/16 18:43:57 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo_flag(char *str)
{
	int	i;
	int count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '-')
			count++;
		i++;
	}
	if (count > 1)
		return (0);
	return (1);
}

void	ft_change_pwd(t_env *env_list, char *old_pwd)
{
	t_env	*tmp;

	tmp = env_list;
	while (env_list)
	{
		if (!(strncmp("PWD", env_list->key, 3)))
		{
			free(env_list->value);
			env_list->value = ft_get_cwd();
		}
		env_list = env_list->next;
	}
	env_list = tmp;
	while (env_list)
	{
		if (!(strncmp("OLDPWD", env_list->key, 7)))
		{
			free(env_list->value);
			env_list->value = old_pwd;
		}
		env_list = env_list->next;
	}
	env_list = tmp;
}