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
	char	*new_line;
	int		fd;

	if (*infile != 0)
		close(*infile);
	fd = open("/tmp/here_doc_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
	line = readline(">");
	new_line = ft_strjoin(line, "\n");
	write(fd, new_line, ft_strlen(new_line));
	while (ft_strncmp(line, input, ft_strlen(input)) != 0)
	{
		free(line);
		free(new_line);
		new_line = NULL;
		line = readline(">");
		if (ft_strncmp(line, input, ft_strlen(input)) != 0)
		{
			new_line = ft_strjoin(line, "\n");
			write(fd, new_line, ft_strlen(new_line));
		}
	}
	free(new_line);
	free(line);
	close(fd);
	if (*infile != 0)
		close(*infile);
	fd = open("/tmp/here_doc_file", O_RDONLY);
	*infile = fd;
	unlink("/tmp/here_doc_file");
	return (fd);
}
