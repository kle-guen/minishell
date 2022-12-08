/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 14:49:22 by chjoie            #+#    #+#             */
/*   Updated: 2022/04/11 15:05:53 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	countsize(int n)
{
	size_t	x;

	x = 0;
	if (n <= 0)
		x++;
	while (n != 0)
	{
		n = n / 10;
		x++;
	}
	return (x);
}

char	*ft_itoa(int n)
{
	char	*tab;
	size_t	x;
	long	nbis;

	nbis = n;
	x = countsize(n);
	tab = malloc(sizeof(char) * countsize(n) + 1);
	if (tab == NULL)
		return (NULL);
	if (nbis < 0)
	{
		tab[0] = '-';
		nbis *= -1;
	}
	tab[x] = '\0';
	x--;
	while (nbis > 9)
	{
		tab[x] = (nbis % 10) + '0';
		nbis /= 10;
		x--;
	}
	tab[x] = (nbis % 10) + '0';
	return (tab);
}
