/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcpy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:38:38 by chjoie            #+#    #+#             */
/*   Updated: 2022/03/29 16:38:40 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	      size_t	x;
	        char	*p;
	unsigned int	i;

	p = (char *) src;
	i = 0;
	x = 0;
	while (src[x])
		x++;
	if (size == 0)
	{
		dst = p;
		return (x);
	}
	while ((i < size - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (x);
}
