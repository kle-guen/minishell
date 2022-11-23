/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 19:56:51 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/23 10:06:12 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_verif_parsing(char **cmd_args)
{
	int	i;
	int tmp;

	i = 0;
	tmp = g_exit_status;
	g_exit_status = 2;
	while (cmd_args[i])
	{
		if ((!cmd_args[i][0] && cmd_args[i + 1] ) || \
			(i && cmd_args[i - 1] && !cmd_args[i][0]))
			cmd_args[i][0] = ' ';
		if ((!(ft_strncmp(cmd_args[i], ">", 2)) || !(ft_strncmp(cmd_args[i], "<", 2))) \
			&& cmd_args[i + 1] == NULL)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
			return (0);
		}
		if ((!(ft_strncmp(cmd_args[i], ">>", 3)) || !(ft_strncmp(cmd_args[i], "<<", 3))) \
			&& cmd_args[i + 1] == NULL)
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n", 2);
			return (0);
		}
		if (!(ft_strncmp(cmd_args[i], ">>>", 3)))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
			return (0);
		}
		if (!(ft_strncmp(cmd_args[i], "<<<", 3)))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
			return (0);
		}
		if ((!(ft_strncmp(cmd_args[i], "|", 1)) && cmd_args[i + 1] == NULL) \
			|| (!(ft_strncmp(cmd_args[i], ">", 1)) && !(ft_strncmp(cmd_args[i], "|", 1)))
			||  (!(ft_strncmp(cmd_args[i], "<", 1)) && !(ft_strncmp(cmd_args[i], "|", 1))))
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
			return (0);
		}
		i++;
	}
	g_exit_status = tmp;
	return (1);
}