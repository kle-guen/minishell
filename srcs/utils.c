/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:59:08 by kle-guen          #+#    #+#             */
/*   Updated: 2022/10/05 17:27:08 by kle-guen         ###   ########.fr       */
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
	int		len;
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

t_env   *ft_env_list(char **envp)
{
    t_env   *env_list;
	int		i;
	int		len;

	i = 0;
	len = ft_strrlen(envp);
	env_list = malloc(sizeof(t_env) * (len + 1));
	while (i < len)
	{
		env_list[i].key = ft_get_key(envp[i]);
		env_list[i].value = ft_get_value(envp[i]); 
	}
}