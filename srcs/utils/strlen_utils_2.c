/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:44:17 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/28 14:45:19 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen_dollar(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '?')
		return (1);
	while (str[i])
	{
		if (!(ft_isalnum(str[i])) && str[i] != '_')
			return (i);
		i++;
	}
	return (i);
}

int	ft_strrlen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
