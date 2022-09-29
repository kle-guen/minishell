/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strrchr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:49:08 by chjoie            #+#    #+#             */
/*   Updated: 2022/04/01 13:56:09 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	x;

	x = ft_strlen(s);
	while (*s)
		s++;
	while (*s != (const char) c && x--)
	{
		s--;
	}
	if (*s == (const char) c)
		return ((char *) s);
	else
		return (NULL);
}
