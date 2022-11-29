/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils_3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 18:41:27 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/29 11:04:41 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_echo_flag(char *str)
{
	int	i;
	int	count;

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

int	ft_key_is_in_env(t_env *env_list, char *key)
{
	int		len_key;
	t_env	*tmp;

	tmp = env_list;
	len_key = ft_strlen(key);
	while (env_list)
	{
		if (!(strncmp(env_list->key, key, len_key)) && \
		(int)ft_strlen(env_list->key) == len_key)
		{
			free(key);
			return (1);
		}
		env_list = env_list->next;
	}
	env_list = tmp;
	free(key);
	return (0);
}

int	ft_contain_pipe_or_redir(char **cmd_args)
{
	int	i;

	i = 0;
	while (cmd_args[i])
	{
		if (!(ft_strncmp(cmd_args[i], "|", 2)) || \
		!(ft_strncmp(cmd_args[i], ">", 2)) || \
		!(ft_strncmp(cmd_args[i], ">>", 3)) || \
		!(ft_strncmp(cmd_args[i], "<", 2)) || \
		!(ft_strncmp(cmd_args[i], "<<", 3)))
			return (1);
		i++;
	}
	return (0);
}

int	ft_is_built_ins(char *cmd)
{
	if (!(ft_strncmp(cmd, "env", 4)))
		return (1);
	else if (!(ft_strncmp(cmd, "export", 7)))
		return (1);
	else if (!(ft_strncmp(cmd, "unset", 6)))
		return (1);
	else if (!(ft_strncmp(cmd, "echo", 5)))
		return (1);
	else if (!(ft_strncmp(cmd, "pwd", 4)))
		return (1);
	else if (!(ft_strncmp(cmd, "cd", 3)))
		return (1);
	else
		return (0);
}
