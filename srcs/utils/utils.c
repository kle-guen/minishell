/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:59:08 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/30 12:29:39 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strjoin_sep(char *s1, char *s2)
{
	int		i;
	size_t	len1;
	char	*str;

	if (!s2)
		s2 = ft_calloc(1, sizeof(char));
	i = 0;
	len1 = ft_strlen(s1);
	str = malloc(sizeof(char) * (len1 + ft_strlen(s2) + 2));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[i - len1])
	{
		str[i] = s2[i - len1];
		i++;
	}
	str[i] = -1;
	str[i + 1] = '\0';
	ft_dfree(s1, s2);
	return (str);
}

char	*ft_strjoin_dfree(char *s1, char *s2)
{
	int		i;
	size_t	len1;
	size_t	len2;
	char	*str;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{	
		str[i] = s1[i];
		i++;
	}
	while (s2[i - len1])
	{
		str[i] = s2[i - len1];
		i++;
	}
	str[i] = '\0';
	ft_dfree(s1, s2);
	return (str);
}

char	*ft_get_key(char *str)
{
	int		i;
	char	*key;

	i = 0;
	key = malloc(sizeof(char) * (ft_strlen_key(str) + 1));
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*ft_get_value(char *str)
{
	int		i;
	int		len_key;
	char	*value;

	if (!(ft_strchr(str, '=')))
		return (NULL);
	i = 0;
	len_key = ft_strlen_key(str);
	value = malloc(sizeof(char) * (ft_strlen(str) - ft_strlen_key(str) + 1));
	while (str[len_key + i + 1])
	{
		value[i] = str[len_key + i + 1];
		i++;
	}
	value[i] = '\0';
	return (value);
}
