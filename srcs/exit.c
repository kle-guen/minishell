/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:47:42 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/05 14:01:19 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_is_not_alpha(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) && str[i])
		i++;
	if (i == ft_strlen(str))
		return (0);
	return (1);
}

char	*get_base(int size)
{
	char	*base;

	if (size == 20)
		base = "-9223372036854775808";
	else
		base = "9223372036854775807";
	return (base);
}

int	is_too_large(char *str)
{
	size_t	size;
	int		i;
	char	*base;

	i = 0;
	if (str == NULL)
		return (0);
	size = ft_strlen(str);
	base = get_base(size);
	if (size > 20)
		return (1);
	else if (size == 20 || size == 19)
	{
		while (str[i])
		{
			if (base[i] == str[i])
				i++;
			else if (base[i] > str[i])
				return (0);
			else
				return (1);
		}
	}
	return (0);
}

void	check_exit_error(t_cmd cmd, t_exec *execution)
{
	if (is_too_large(cmd.av[1]) == 1)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		ft_free_execution(execution);
		exit (2);
	}
	if (ft_is_not_alpha(cmd.av[1]) == 1)
	{
		printf("exit\n");
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		ft_free_execution(execution);
		exit (2);
	}
}

void	ft_exit_built(t_cmd cmd, t_exec *execution)
{
	int	value;

	check_exit_error(cmd, execution);
	if (cmd.av[1])
	{
		if (cmd.av[2] != NULL)
		{
			printf("exit\n");
			g_exit_status = 1;
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		}
		else
		{
			value = ft_atoi(cmd.av[1]);
			printf("exit\n");
			ft_free_execution(execution);
			exit(value);
		}
	}
	else
	{
		printf("exit\n");
		ft_free_execution(execution);
		exit(0);
	}
}
