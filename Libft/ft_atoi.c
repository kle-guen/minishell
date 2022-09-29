/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:49:26 by chjoie            #+#    #+#             */
/*   Updated: 2022/09/20 11:31:02 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int			x;
	int			sign;
	int	result;

	result = 0;
	x = 0;
	sign = 1;
	while (nptr[x] == ' ' || nptr[x] == '\t' || nptr[x] == '\r' \
			|| nptr[x] == '\n' || nptr[x] == '\v' || nptr[x] == '\f')
	if (nptr[x] == '-')
	{
		sign = sign * -1;
		x++;
	}
	while (nptr[x] >= '0' && nptr[x] <= '9')
	{
		result = result * 10;
		result = result + (nptr[x] - '0');
		x++;
	}
	result = result * sign;
	return (result);
}

