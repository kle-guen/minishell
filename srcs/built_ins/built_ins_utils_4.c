/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins_utils_4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 13:55:54 by kle-guen          #+#    #+#             */
/*   Updated: 2022/12/07 13:23:49 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_trim_quotes(char *str, char quote, int *len)
{
	int		i;
	int		count;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	count = 0;
	new_str = malloc(sizeof(char) * (ft_strlen(str) - 1));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] != quote || count > 1)
			new_str[j++] = str[i];
		else
			count++;
		i++;
	}
	new_str[j] = '\0';
	*len -= 2;
	return (new_str);
}

void	ft_remove_quotes(char **str, int *len, char quote)
{
	char	*tmp;

	tmp = ft_trim_quotes(*str, quote, len);
	free(*str);
	*str = tmp;
}

void	ft_reparsing(char **cmd_args)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	while (cmd_args[i])
	{
		len = ft_strlen(cmd_args[i]);
		while (j < len)
		{
			if (cmd_args[i][j] == 39 && ft_strchr("><|", cmd_args[i][j + 1]) \
			&& ft_is_close_quotes(&cmd_args[i][j + 1], 39))
				ft_remove_quotes(&cmd_args[i], &len, 39);
			else if (cmd_args[i][j] == '"' && \
			ft_strchr("><|", cmd_args[i][j + 1]) && \
			ft_is_close_quotes(&cmd_args[i][j + 1], '"'))
				ft_remove_quotes(&cmd_args[i], &len, '"');
			else
				j++;
		}
		j = 0;
		i++;
	}
}
