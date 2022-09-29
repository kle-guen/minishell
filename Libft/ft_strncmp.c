/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:23:07 by chjoie            #+#    #+#             */
/*   Updated: 2022/03/29 14:23:19 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	       size_t	i;
	unsigned char	*casts1;
	unsigned char	*casts2;

	casts1 = (unsigned char *) s1;
	casts2 = (unsigned char *) s2;
	i = 0;
	if ((int) n < 0)
		return (-1);
	if (n == 0)
		return (0);
	while ((i < n - 1) && (casts1[i] != '\0'))
	{
		if (casts1[i] != casts2[i])
			return (casts1[i] - casts2[i]);
		else
			i++;
	}
	return (casts1[i] - casts2[i]);
}
