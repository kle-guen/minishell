/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:04:11 by chjoie            #+#    #+#             */
/*   Updated: 2022/04/14 16:27:23 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <unistd.h>
#include <string.h>

int	ft_lstsize(t_list *lst)
{
	int	x;

	x = 1;
	if (lst == NULL)
		return (0);
	while (lst->next != NULL)
	{
		x++;
		lst = lst->next;
	}
	return (x);
}
