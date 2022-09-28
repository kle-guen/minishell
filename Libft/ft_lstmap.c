/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 15:52:05 by kle-guen          #+#    #+#             */
/*   Updated: 2022/09/28 21:49:54 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_add;

	new_add = ft_lstnew(f(lst->content));
	if (!new_add)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	lst = lst->next;
	new = new_add;
	while (lst)
	{
		new_add = ft_lstnew(f(lst->content));
		if (!new_add)
		{
			ft_lstclear(&lst, del);
			ft_lstclear(&new_add, del);
			break ;
		}
		ft_lstadd_back(&new, new_add);
		lst = lst->next;
	}
	return (new);
}
