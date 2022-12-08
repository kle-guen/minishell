/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:31:01 by chjoie            #+#    #+#             */
/*   Updated: 2022/04/08 12:11:36 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	isfound(char c, char const *set)
{
	size_t	x;
	size_t	y;

	y = 0;
	x = 0;
	while (set[y] != '\0')
	{
		if (set[y] == c)
			x++;
		y++;
	}
	return (x);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	x;
	size_t	cpt;
	size_t	cpt2;

	cpt2 = 0;
	cpt = 0;
	x = 0;
	if (s1 == NULL)
		return (NULL);
	while (isfound(s1[x], set))
	{
		cpt++;
		x++;
	}
	x = ft_strlen(s1) - 1;
	while (isfound(s1[x], set))
	{
		x--;
		cpt2++;
	}
	x = isfound(s1[0], set);
	return (ft_substr(s1, cpt, ft_strlen(s1) - cpt - cpt2));
}
