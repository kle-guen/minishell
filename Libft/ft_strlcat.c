/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:41:35 by chjoie            #+#    #+#             */
/*   Updated: 2022/04/08 18:15:43 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	x;
	size_t	y;

	y = 0;
	x = 0;
	len = ft_strlen(src);
	while (dst[x] && x < size)
		x++;
	while (src[y] && x + y + 1 < size)
	{
		dst[x + y] = src[y];
		y++;
	}
	if (x != size)
		dst[x + y] = '\0';
	return (len + x);
}
