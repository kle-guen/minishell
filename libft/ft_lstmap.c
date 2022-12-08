/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 10:28:01 by chjoie            #+#    #+#             */
/*   Updated: 2022/04/15 16:21:52 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*start;
	t_list	*new;
	t_list	*clone;

	if (lst == NULL)
		return (NULL);
	start = ft_lstnew((*f)(lst->content));
	if (start == NULL)
		return (NULL);
	clone = lst->next;
	while (clone)
	{
		new = ft_lstnew((*f)(clone->content));
		if (new == NULL)
		{
			ft_lstclear(&clone, del);
			return (NULL);
		}
		ft_lstadd_back(&start, new);
		clone = clone->next;
	}
	new = NULL;
	return (start);
}
