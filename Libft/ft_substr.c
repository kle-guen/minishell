/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:36:40 by chjoie            #+#    #+#             */
/*   Updated: 2022/11/30 17:06:59 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	int		x;

	x = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
	{
		substr = ft_calloc(sizeof(char), 1);
		return (substr);
	}
	else if (len >= ft_strlen(s))
		substr = ft_calloc(sizeof(char), ft_strlen(s) - start + 1);
	else
		substr = ft_calloc(sizeof(char), len + 1);
	if (substr == NULL)
		return (NULL);
	while (s[start] != '\0' && len != 0 && s[x] != '\0')
	{
		substr[x] = s[start];
		x++;
		start++;
		len--;
	}
	return (substr);
}
