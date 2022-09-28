/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/03 15:57:17 by kle-guen          #+#    #+#             */
/*   Updated: 2022/09/28 21:49:54 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*des;
	char	*str;

	i = 0;
	if (!dest && !src)
		return (NULL);
	des = (char *)dest;
	str = (char *)src;
	if (dest > src)
	{
		while (i < n)
		{
			des[n - i - 1] = str[n - i - 1];
			i++;
		}
	}
	else
		return (ft_memcpy(dest, src, n));
	return (des);
}
