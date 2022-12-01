/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_after_parsing2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 15:56:51 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/01 15:56:52 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	is_unclosed(char *str)
{
	if (*str == '\"')
	{
		str++;
		if (ft_strchr(str, '\"'))
			return (1);
		else
			return (0);
	}
	if (*str == '\'')
	{
		str++;
		if (ft_strchr(str, '\''))
			return (1);
		else
			return (0);
	}
	return (1);
}
