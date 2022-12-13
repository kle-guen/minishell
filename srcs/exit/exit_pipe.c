/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 18:23:41 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/13 18:23:43 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_exit_error_pipe(t_cmd cmd, t_exec *execution)
{
	if (is_too_large(cmd.av[1]) == 1)
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		ft_free_execution(execution);
		exit(2);
	}
	if (ft_is_not_alpha(cmd.av[1]) == 1)
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		ft_free_execution(execution);
		exit(2);
	}
}

void	exit_in_pipe(t_exec *execution, int cmd_nb)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	check_exit_error_pipe(execution->cmd_list[cmd_nb], execution);
	if (execution->cmd_list[cmd_nb].av[2] != NULL)
	{
		g_exit_status = 1;
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
	}
	if (execution->cmd_list[cmd_nb].av[1][0] == '-' ||
		execution->cmd_list[cmd_nb].av[1][0] == '+')
		i++;
	while (execution->cmd_list[cmd_nb].av[1][i])
	{
		if (!ft_isdigit(execution->cmd_list[cmd_nb].av[1][i]))
			x = 1;
		i++;
	}
	if (x == 0)
		g_exit_status = ft_atoi(execution->cmd_list[cmd_nb].av[1]);
}
