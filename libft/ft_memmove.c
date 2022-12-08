/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 12:17:59 by chjoie            #+#    #+#             */
/*   Updated: 2022/03/29 12:32:01 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*p;
	char	*s;
	char	*endd;
	char	*ends;

	s = (char *)src;
	p = (char *)dest;
	endd = p + (n - 1);
	ends = s + (n - 1);
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
	{
		while (n--)
		{
			*endd = *ends;
			endd--;
			ends--;
		}
	}
	return (dest);
}
