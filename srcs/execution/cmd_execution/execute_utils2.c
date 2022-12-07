/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:21:31 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/05 15:28:29 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	child_last_cmd(t_exec *execution, int *pipefd, int cmd_nb)
{
	ft_if_after_buitin(execution, cmd_nb);
	setup_last_cmd(&execution->cmd_list[cmd_nb].cmd_fd[0], \
		&execution->cmd_list[cmd_nb].cmd_fd[1], pipefd);
	close_pipe(pipefd);
	execute(execution, cmd_nb);
}

void	ft_if_after_buitin(t_exec *execution, int cmd_nb)
{
	int	i;

	i = 0;
	if (execution->cmd_list[cmd_nb - 1].av[0]
		&& ft_is_built_ins(execution->cmd_list[cmd_nb - 1].av[0]) == 1
		&& execution->cmd_list[cmd_nb].av[0]
		&& ft_is_built_ins(execution->cmd_list[cmd_nb].av[0]) == 0)
	{
		while (i < 10000000)
			i++;
	}
}
