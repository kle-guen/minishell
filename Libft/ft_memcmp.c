/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 13:34:14 by chjoie            #+#    #+#             */
/*   Updated: 2022/11/30 16:49:58 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str;
	unsigned char	*str2;
	size_t			x;

	x = 0;
	str = (unsigned char *) s1;
	str2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (x < n - 1)
	{
		if (str[x] < str2[x])
			return (str[x] - str2[x]);
		else if (str[x] > str2[x])
			return (str[x] - str2[x]);
		else
			x++;
	}
	return (str[x] - str2[x]);
}
