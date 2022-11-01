/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:58:00 by chjoie            #+#    #+#             */
/*   Updated: 2022/11/01 10:58:04 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

void	create_fork(t_command command, char **envp)
{
	pid_t	child_id;

	child_id = fork();
	if (child_id == 0)
		execve(command.path, command.av, envp);
	waitpid(child_id, NULL, 0);
}

void	execute_one_cmd(t_command command)
{
	if (command.av[0] != NULL)
	{
		if (command.path!= NULL)
			create_fork(command, NULL);
		else
			printf("%s: command not found\n", command.av[0]);
	}
}
