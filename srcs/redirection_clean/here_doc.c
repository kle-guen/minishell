/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:39:42 by chjoie            #+#    #+#             */
/*   Updated: 2022/11/04 10:05:29 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

int	here_doc(int *infile, const char *input)
{
	char	*line;
	int		fd;

	if (*infile != 0)
		close(*infile);
	//clear le doc ?
	fd = open("here_doc_file", O_WRONLY | O_CREAT | O_APPEND, 0644);
	line = readline(">");
	//ajout du \n
	write(fd, line, ft_strlen(line));
	while (ft_strncmp(line, input, ft_strlen(input)) != 0)
	{
		free(line);
		line = readline(">");
		if (ft_strncmp(line, input, ft_strlen(input)) != 0)
		{
				write(fd, line, ft_strlen(line));
		}
	}
	*infile = fd;
//	close(fd);
	free(line);
	return (fd);
}
