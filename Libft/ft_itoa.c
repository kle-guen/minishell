/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 15:11:56 by kle-guen          #+#    #+#             */
/*   Updated: 2022/09/28 21:49:54 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static	int	ft_lennb(int n)
{
	int	i;

	i = 1;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n / 10 > 0)
	{	
		i++;
		n /= 10;
	}
	return (i);
}

static	void	ft_intmin(char *str)
{
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = '\0';
}

static	void	ft_fill(char *str, int n, int len)
{
	int	i;

	i = 1;
	if (n < 0)
	{	
		n *= -1;
		str[0] = '-';
	}
	while (i < len)
	{
		str[len - i] = n % 10 + 48;
		n /= 10;
		i++;
	}
	if (str[0] != '-')
		str[0] = n + 48;
	str[len] = '\0';
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;

	if (n == -2147483648)
	{
		str = ft_calloc(sizeof(char), 12);
		ft_intmin(str);
		return (str);
	}
	len = ft_lennb(n);
	str = ft_calloc(sizeof(char), (len + 1));
	if (!str)
		return (NULL);
	ft_fill(str, n, len);
	return (str);
}
