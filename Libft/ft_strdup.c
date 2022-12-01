/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 16:47:03 by chjoie            #+#    #+#             */
/*   Updated: 2022/11/30 16:53:19 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;
	int		x;

	x = 0;
	len = ft_strlen(s);
	dup = malloc(sizeof(*dup) * len + 1);
	if (dup == NULL)
		return (NULL);
	while (s[x] != 0)
	{
		dup[x] = s[x];
		x++;
	}
	dup[x] = '\0';
	return (dup);
}
