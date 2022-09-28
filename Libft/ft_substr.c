/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:53:56 by kle-guen          #+#    #+#             */
/*   Updated: 2022/09/28 21:49:54 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	int		j;
	size_t	lenstr;
	char	*new;

	lenstr = ft_strlen(s);
	if (start > lenstr)
	{
		new = ft_calloc(1, sizeof(char));
		if (!new)
			return (NULL);
		return (new);
	}
	else if (start + len < lenstr)
		new = malloc(sizeof(char) * (len + 1));
	else
		new = malloc(sizeof(char) * (lenstr - start + 1));
	if (!new)
		return (NULL);
	i = 0;
	j = start;
	while (i < len && s[j])
		new[i++] = s[j++];
	new[i] = '\0';
	return (new);
}
