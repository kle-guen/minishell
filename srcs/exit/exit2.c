/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 11:07:51 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/12 11:07:52 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_shell(char **cmd_args, char *input, t_env **env_list, int value)
{
	printf("exit\n");
	ft_free_tab(cmd_args);
	free(input);
	ft_free_env(env_list);
	exit(value);
}

void	ft_exit(char **cmd_args, char *input, t_env **env_list)
{
	if (cmd_args[1] != NULL)
		return ;
	printf("exit\n");
	ft_free_tab(cmd_args);
	free(input);
	ft_free_env(env_list);
	exit(g_exit_status);
}
