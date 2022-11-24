/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:39:42 by chjoie            #+#    #+#             */
/*   Updated: 2022/11/23 07:09:01 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include "../../includes/libft.h"

void	ctrl_here(int signal)
{
	(void) signal;
	close(0);
	g_exit_status = -2;

}

void	ft_free_here_doc(char *line, char *delimiter, int fd, int code)
{
	free(line);
	close(fd);
	free(delimiter);
	exit(code);
}

void	while_here_doc(char *delimiter, int fd)
{
	char *line = NULL;
	
	while (1)
	{
		line = readline(">");
		if (line == NULL)
		{
			if (g_exit_status != -2)
				printf("warning: here-document delimited by \
				end-of-file (wanted '%s')\n", delimiter);
			else
				ft_free_here_doc(line, delimiter, fd, 2);
			ft_free_here_doc(line, delimiter, fd, 1);
		}
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter) != 0))
			ft_putendl_fd(line, fd);
		else
			ft_free_here_doc(line, delimiter, fd, 0);	
		free(line);
	}
}

void	here_doc(char *delimiter, char **cmd_args, t_env *env_list, int fd)
{
	pid_t	child_id;
	int	status;
	close(fd);
	fd = open("/tmp/.here_doc_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
	child_id = fork();
	if (child_id == 0)
	{
		signal(SIGINT, ctrl_here);
		ft_free_env(&env_list);
		free_str_tab(cmd_args);
		while_here_doc(delimiter, fd);
	}
	waitpid(child_id, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 2)
			g_exit_status = -2;
	}
	close(fd);
}

int	here_doc_redir(int *cmd_input_fd)
{
	int	file_fd;
	char	*file_error;
	
	file_error = NULL;
	if (*cmd_input_fd != 0)
		close(*cmd_input_fd);
	file_fd = open("/tmp/.here_doc_file", O_RDONLY);
	if (file_fd == -1)
	{
		file_error = error_msg("here doc");
		perror(file_error);
		free(file_error);
		return (file_fd);
	}
	*cmd_input_fd = file_fd;
	return (file_fd);
}
