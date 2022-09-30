/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:10:31 by chjoie            #+#    #+#             */
/*   Updated: 2022/04/06 17:10:37 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*fillstr(char *result, const char *s2, size_t y)
{
	size_t	x;

	x = 0;
	while (s2[x] != '\0')
	{
		result[y] = s2[x];
		y++;
		x++;
	}
	result[y] = '\0';
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	  char	*result;
	size_t	y;

	y = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	result = ft_calloc(sizeof(*result), len + 1);
	if (result == NULL)
		return (NULL);
	while (s1[y] != '\0')
	{
		result[y] = s1[y];
		y++;
	}
	result = fillstr(result, s2, y);
	free(s2);
	return (result);
}
