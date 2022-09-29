/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 10:06:13 by chjoie            #+#    #+#             */
/*   Updated: 2022/04/04 10:06:16 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	x;
	size_t	len_bis;

	x = 0;
	if (*little == '\0')
		return ((char *) big);
	while (big[x] != '\0' && len > 0 && (x < ft_strlen(little)))
	{
		len_bis = len;
		while (little[x] == big[x] && len_bis)
		{
			if (x + 1 == ft_strlen(little) && (little[x] == big[x]))
				return ((char *) big);
			x++;
			len_bis--;
		}
		x = 0;
		big++;
		len--;
	}
	return (0);
}
