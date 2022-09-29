/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 18:47:01 by chjoie            #+#    #+#             */
/*   Updated: 2022/04/15 16:24:12 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <unistd.h>
#include <string.h>

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*p;
	t_list	*p2;

	if (lst == NULL)
		return ;
	p = *lst;
	while (p != NULL)
	{
		p2 = p->next;
		ft_lstdelone(p, del);
		p = p2;
	}
	*lst = NULL;
}
