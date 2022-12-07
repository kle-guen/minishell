/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:31:52 by kle-guen          #+#    #+#             */
/*   Updated: 2022/12/07 13:05:58 by kle-guen         ###   ########.fr       */
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

void	ft_echo(char **cmd_args)
{
	int	i;

	i = 1;
	if (!(ft_strncmp(cmd_args[1], "-n", 2)) && \
	ft_echo_flag(cmd_args[1]))
		ft_echo_no_nl(cmd_args);
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

void	ft_launch_cd(char **cmd_args, t_env **env_list)
{
	if (!cmd_args[1])
		ft_cd(ft_get_env("HOME", *env_list), *env_list);
	else if (cmd_args[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		g_exit_status = 1;
	}
	else
		ft_cd(cmd_args[1], *env_list);
}

void	ft_lauch_echo(char **cmd_args)
{
	if (cmd_args[1])
		ft_echo(cmd_args);
	else
		printf("\n");
}

int	ft_built_ins(char **cmd_args, t_env **env_list)
{
	if (ft_contain_pipe_or_redir(cmd_args))
		return (0);
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
