/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:08:52 by chjoie            #+#    #+#             */
/*   Updated: 2022/04/12 15:08:54 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f) (unsigned int, char))
{
	size_t		y;
	size_t		x;
	  char		*s2;

	x = 0;
	y = 0;
	if (!s)
		return (NULL);
	s2 = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	if (s2 == NULL)
		return (NULL);
	while (s[y] != '\0')
	{
		s2[x] = f(y, s[y]);
		x++;
		y++;
	}
	s2[x] = '\0';
	return (s2);
}
