/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:38:47 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/01 15:38:49 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	ft_built_ins_pipe(char **cmd_args, t_env **env_list)
{
	if (ft_is_built_ins(cmd_args[0]))
		ft_reparsing(cmd_args);
	if (!(ft_strncmp(cmd_args[0], "env", 4)))
		ft_env(*env_list);
	else if (!(ft_strncmp(cmd_args[0], "export", 7)))
		ft_export(*env_list, &cmd_args[1]);
	else if (!(ft_strncmp(cmd_args[0], "unset", 6)))
		ft_unset(env_list, &cmd_args[1]);
	else if (!(ft_strncmp(cmd_args[0], "echo", 5)))
		ft_lauch_echo(cmd_args);
	else if (!(ft_strncmp(cmd_args[0], "pwd", 4)))
		ft_pwd();
	else if (!(ft_strncmp(cmd_args[0], "cd", 3)))
		ft_launch_cd(cmd_args, env_list);
	else
		return (0);
	return (1);
}

int	get_env_size(t_env **root)
{
	int		i;
	t_env	*list;

	list = *root;
	i = 0;
	while (list->next)
	{
		list = list->next;
		i++;
	}
	i++;
	return (i);
}

char	**get_exec_env(t_env **root)
{
	char	**env;
	t_env	*list;
	char	*start;
	int		i;

	list = *root;
	env = malloc(sizeof(char **) * (get_env_size(root) + 1));
	i = 0;
	while (list->next)
	{
		start = ft_strjoin(list->key, "=");
		env[i] = ft_strjoin(start, list->value);
		free(start);
		list = list->next;
		i++;
	}
	start = ft_strjoin(list->key, "=");
	env[i] = ft_strjoin(start, list->value);
	i++;
	env[i] = NULL;
	free(start);
	return (env);
}
