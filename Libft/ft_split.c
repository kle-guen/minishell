/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 16:58:41 by kle-guen          #+#    #+#             */
/*   Updated: 2022/09/28 21:49:54 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static	int	ft_count_str(char const *s, char c)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if ((s[i] == c && s[i + 1] != c) || s[i + 1] == '\0')
			count++;
		i++;
	}
	return (count);
}

static	void	ft_lensplit(char const *s, int *tab, char c)
{
	int		len;
	int		indice;

	len = 0;
	indice = tab[1];
	while (s[indice] == c && s[indice])
		indice++;
	while (s[indice] != c && s[indice])
	{
		len++;
		indice++;
	}
	tab[0] = len;
	tab[1] = indice;
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		count;
	char	**tab;
	int		len_indice[2];

	i = 0;
	len_indice[0] = 0;
	len_indice[1] = 0;
	count = ft_count_str(s, c);
	tab = malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	ft_lensplit(s, len_indice, c);
	while (i < count)
	{
		tab[i] = ft_substr(s, len_indice[1] - len_indice[0], len_indice[0]);
		ft_lensplit(s, len_indice, c);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
