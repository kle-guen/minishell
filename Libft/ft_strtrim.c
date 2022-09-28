/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:08:54 by kle-guen          #+#    #+#             */
/*   Updated: 2022/09/28 21:49:54 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	is_set_in_str(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{	
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

size_t	len_str(char const *s1, char const *set)
{
	size_t	len;
	int		i;

	len = ft_strlen(s1);
	i = 0;
	while (is_set_in_str(s1[len - 1], set) && len > 0)
		len--;
	while (is_set_in_str(s1[i++], set) && len > 0)
		len--;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = len_str(s1, set);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	while (is_set_in_str(s1[i], set) && s1[i])
		i++;
	while (j < len)
		new[j++] = s1[i++];
	new[j] = '\0';
	return (new);
}
