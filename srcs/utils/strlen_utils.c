/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 11:05:44 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/28 16:36:00 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (i);
}

int	ft_strlen_key_plus(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
			return (i);
		i++;
	}
	return (i);
}

int	ft_strlen_noquote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '$' && str[i + 1]) || ft_strchr("|><", str[i]))
			return (i);
		i++;
	}
	return (i);
}

int	ft_strlen_quote(char *str, char quote)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == quote)
			return (i);
		i++;
	}
	return (i + 1);
}

int	ft_strlen_redir(char *str, char redir)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != redir)
			return (i);
		i++;
	}
	return (i);
}
