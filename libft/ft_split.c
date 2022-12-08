/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:17:25 by chjoie            #+#    #+#             */
/*   Updated: 2022/04/12 16:13:52 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	wordsize(char const *s, char c, size_t x)
{
	size_t	y;

	y = 0;
	if (s[x] == c)
	{
		while (s[x] == c && s[x] != '\0')
			x++;
	}
	while (s[x] && s[x] != c)
	{
		x++;
		y++;
	}
	return (y);
}

static size_t	wordcount(char const *s, char c)
{
	size_t	x;
	size_t	y;

	y = 0;
	x = 0;
	while (s[x] != '\0')
	{
		if (s[x] != c)
		{
			y++;
			while (s[x] != c && s[x] != '\0')
				x++;
		}
		else
			x++;
	}
	return (y);
}

char	**ft_split(char const *s, char c)
{
	size_t	x;
	size_t	y;
	char	**result;

	x = 0;
	y = 0;
	if (!s)
		return (NULL);
	result = ft_calloc(sizeof(char *), wordcount(s, c) + 1);
	if (result == NULL)
		return (NULL);
	while (y < wordcount(s, c) && s[x] != '\0')
	{
		if (s[x] == c)
			while (s[x] == c && s[x] != '\0')
				x++;
		result[y] = ft_substr(s, x, wordsize(s, c, x));
		while (s[x] != '\0' && s[x] != c)
			x++;
		y++;
	}
	return (result);
}
