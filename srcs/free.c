/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:45:54 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/16 19:21:53 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_free_env_var(t_env *env_var)
{
		free(env_var->value);
		free(env_var->key);
		free(env_var);
}

void	ft_free_env(t_env **envp)
{
	t_env	*tmp;

	while (*envp)
	{
		tmp = *envp;
		*envp = (*envp)->next;
		free(tmp->value);
		free(tmp->key);
		free(tmp);
	}
}