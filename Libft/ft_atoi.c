/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:49:26 by chjoie            #+#    #+#             */
/*   Updated: 2022/11/30 16:46:57 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_convert(char *str)
{
	size_t	x;
	int		nb;

	x = 0;
	nb = str[x] - '0';
	while (x != ft_strlen(str) - 1)
	{
		nb = nb * 10 + str[x + 1] - '0';
		x++;
	}
	return (nb);
}

static int	ft_get_number(int x, int y, char *nptr, char *snbr)
{
	while (nptr[x] >= '0' && nptr[x] <= '9')
	{
		snbr[y] = nptr[x];
		x++;
		y++;
	}
	return (y);
}

int	ft_atoi(const char *nptr)
{
	char	snbr[99];
	size_t	x;
	int		sign;
	int		y;

	sign = 1;
	x = 0;
	y = 0;
	while (nptr[x] == ' ' || nptr[x] == '\t' || nptr[x] == '\r' \
	|| nptr[x] == '\n' || nptr[x] == '\v' || nptr[x] == '\f')
		x++;
	if (nptr[x] == '+' || nptr[x] == '-')
	{
		if (nptr[x] == '-')
			sign = sign * (-1);
		x++;
	}
	if (nptr[x] >= '0' && nptr[x] <= '9')
		y = ft_get_number(x, y, (char *)nptr, snbr);
	else
		return (0);
	snbr[y] = '\0';
	return (ft_convert(snbr) * sign);
}
