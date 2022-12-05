/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:59:44 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/28 14:06:33 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_env(t_env *env_list)
{
	ft_print_env(env_list);
}

void	ft_pwd(void)
{
	char	*buff;

	buff = ft_get_cwd();
	printf("%s\n", buff);
	free(buff);
}

void	ft_cd(char *path, t_env *env_list)
{
	int		i;
	char	*pwd;

	if (!path)
	{
		ft_putstr_fd("minishell: HOME not set\n", 2);
		g_exit_status = 1;
		return ;
	}	
	pwd = ft_get_cwd();
	i = chdir(path);
	if (i == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		g_exit_status = 1;
		free(pwd);
	}
	else
		ft_change_pwd(env_list, pwd);
}

void	ft_export(t_env *env_list, char **cmd_args)
{
	int		i;

	i = 0;
	while (cmd_args[i])
	{
		ft_add_env(env_list, cmd_args[i]);
		i++;
	}
	if (!i)
		ft_print_export(env_list);
}

void	ft_unset(t_env **env_list, char **cmd_args)
{
	int		i;
	int		len_key;

	i = 0;
	while (cmd_args[i])
	{
		len_key = ft_strlen(cmd_args[i]);
		ft_remove_env(env_list, cmd_args[i], len_key, *env_list);
		i++;
	}
}
