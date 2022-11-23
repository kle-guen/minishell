/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:31:52 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/23 17:40:53 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_ctrl_c(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	if (g_exit_status != -1)
		rl_redisplay();
	g_exit_status = 130;
}

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

void	ft_echo(char **cmd_args)
{
	int				i;

	i = 1;
	if (!(ft_strncmp(cmd_args[1], "-n", 2)) && ft_echo_flag(cmd_args[1]) && cmd_args[i + 1])
	{
		i++;
		while (cmd_args[i + 1])
		{
			printf("%s ", cmd_args[i]);
			i++;
		}
		printf("%s", cmd_args[i]);
	}
	else
	{
		while (cmd_args[i + 1])
		{
			printf("%s ", cmd_args[i]);
			i++;
		}
		printf("%s\n", cmd_args[i]);
	}
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
		!(ft_strncmp(cmd_args[i], "<<", 3))) \
			return (1);
		i++;
	}
	return (0);
}

int ft_is_built_ins(char *cmd)
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

void	ft_reparsing(char **cmd_args)
{
	int		i;
	char	*tmp;
	
	i = 0;
	while (cmd_args[i])
	{
		if ((cmd_args[i][0] == 39 && ft_is_close_quotes(cmd_args[i], 39)) \
		|| (cmd_args[i][0] == '"' && ft_is_close_quotes(cmd_args[i], '"')))
		{
			tmp = ft_substr(cmd_args[i], 1, ft_strlen(cmd_args[i]) - 2);
			free(cmd_args[i]);
			cmd_args[i] = tmp;
		}
		i++;
	}
}

int	ft_built_ins(char **cmd_args, t_env **env_list)
{
	if (ft_contain_pipe_or_redir(cmd_args))
		return (0);
	ft_reparsing(cmd_args);
	if (!(ft_strncmp(cmd_args[0], "env", 4)))
		ft_env(*env_list);
	else if (!(ft_strncmp(cmd_args[0], "export", 7)))
		ft_export(*env_list, &cmd_args[1]);
	else if (!(ft_strncmp(cmd_args[0], "unset", 6)))
		ft_unset(env_list, &cmd_args[1]);
	else if (!(ft_strncmp(cmd_args[0], "echo", 5)))
	{	
		if (cmd_args[1])
			ft_echo(cmd_args);
		else
			printf("\n");
	}
	else if (!(ft_strncmp(cmd_args[0], "pwd", 4)))
		ft_pwd();
	else if (!(ft_strncmp(cmd_args[0], "cd", 3)))
	{
		if (!cmd_args[1])
			ft_cd(ft_get_env("HOME", *env_list), *env_list);
		else if (cmd_args[2])
		{
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
			g_exit_status = 1;
		}
		else
			ft_cd(cmd_args[1] , *env_list);
	}
	else
		return (0);
	return (1);
}
