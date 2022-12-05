/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 14:03:30 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/05 13:57:28 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

char	*add_slash(char *str)
{
	char	*new_str;
	int		size;
	int		x;
	int		y;

	y = 0;
	x = 0;
	size = ft_strlen(str);
	new_str = malloc(sizeof(char) * size + 2);
	if (!new_str)
		return (NULL);
	new_str[y] = '/';
	y++;
	while (str[x])
	{
		new_str[y] = str[x];
		x++;
		y++;
	}
	new_str[y] = '\0';
	return (new_str);
}

int	check_directory_error(char *command)
{
	if (*command == '/' || *command == '.')
	{
		if (!access(command, X_OK) && !check_directory(command))
			return (1);
		else
		{
			if (errno == EACCES && g_exit_status != 126)
			{
				perror(command);
				g_exit_status = 126;
			}
			else if (g_exit_status != 126)
			{
				perror(command);
				g_exit_status = 127;
			}
			return (2);
		}
	}
	return (0);
}
