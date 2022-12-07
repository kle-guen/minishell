/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 16:59:08 by kle-guen          #+#    #+#             */
/*   Updated: 2022/12/07 14:04:58 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fill_strjoin(char *s1, char *s2, char *str, int len1)
{
	int	i;

	i = 0;
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
}

char	*ft_strjoin_sep(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	if (!s1)
	{
		free(s2);
		return (NULL);
	}
	if (!s2)
	{
		str = ft_strdup(s1);
		free(s1);
		return (str);
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len1 + len2 + 2));
	if (!str)
		return (NULL);
	fill_strjoin(s1, s2, str, len1);
	str[len1 + len2] = -1;
	str[len1 + len2 + 1] = '\0';
	ft_dfree(s1, s2);
	return (str);
}

char	*ft_strjoin_dfree(char *s1, char *s2)
{
	size_t	len1;
	size_t	len2;
	char	*str;

	if (!s1 || !s2)
	{
		ft_dfree(s1, s2);
		return (NULL);
	}
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	fill_strjoin(s1, s2, str, len1);
	str[len1 + len2] = '\0';
	ft_dfree(s1, s2);
	return (str);
}

char	*ft_get_key(char *str)
{
	int		i;
	char	*key;
	int		len_key;

	i = 0;
	len_key = ft_strlen_key(str);
	key = malloc(sizeof(char) * (len_key + 1));
	if (!key)
		return (NULL);
	while (i < len_key)
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
	value = malloc(sizeof(char) * (ft_strlen(str) - len_key));
	if (!value)
		return (NULL);
	while (str[len_key + i + 1])
	{
		value[i] = str[len_key + i + 1];
		i++;
	}
	value[i] = '\0';
	return (value);
}
