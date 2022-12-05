/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 11:39:42 by chjoie            #+#    #+#             */
/*   Updated: 2022/12/01 11:59:28 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	empty_line(char *delimiter, int fd, char *line)
{
	if (g_exit_status != -2)
		print_here_doc_error(delimiter);
	else
		ft_free_here_doc(line, delimiter, fd, 2);
	ft_free_here_doc(line, delimiter, fd, 1);
}	

void	here_doc_loop(char *delimiter, int fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = readline(">");
		if (line == NULL)
			empty_line(delimiter, fd, line);
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
	int		status;

	close(fd);
	fd = open("/tmp/.here_doc_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
	child_id = fork();
	signal(SIGINT, SIG_IGN);
	if (child_id == 0)
	{
		signal(SIGINT, ctrl_here);
		ft_free_env(&env_list);
		free_str_tab(cmd_args);
		here_doc_loop(delimiter, fd);
	}
	waitpid(child_id, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) == 2)
			g_exit_status = -2;
	}
	signal(SIGINT, ft_ctrl_c);
	close(fd);
}

int	check_here_doc(char **cmd_args, t_env *env_list)
{
	int	x;
	int	fd;

	x = 0;
	if (check_input(cmd_args[x]) == 1)
	{
		clear_here_doc();
		fd = open("/tmp/.here_doc_file", O_RDWR | O_CREAT | O_TRUNC, 0644);
		while (cmd_args[x] != NULL)
		{
			if (is_separator(cmd_args[x]) && what_separator(cmd_args[x]) == 3)
			{
				x++;
				launch_here_doc(cmd_args, env_list, fd, x);
				if (g_exit_status == -2)
				{
					close_here_doc(fd);
					return (0);
				}
			}
			x++;
		}
		close(fd);
	}
	return (1);
}

int	here_doc_redir(int *cmd_input_fd)
{
	int		file_fd;
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
