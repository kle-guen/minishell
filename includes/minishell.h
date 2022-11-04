/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:23:16 by kle-guen          #+#    #+#             */
/*   Updated: 2022/10/05 17:36:30 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"

typedef struct s_env
{
    char *key;
    char *value;
}               t_env;

typedef struct	s_command
{
	char **av; //command a execve
	int  cmd_fd[2];
	char	*path;
//	pid_t	child_id;
}		t_command;

/**** find path ****/
char	*add_slash(char *str);
char	*find_path(char *command, char *path);
void	free_str_tab(char **tab_str);
char	*get_path(char *command, char *path);

//void	execute_cmd(char *input, char **envp);
pid_t	execute_cmd(t_command command, int *pipefd1, int *pipefd2);

/**** input parsing ****/
int     *ft_input_map(char *input);
char	*ft_parse_input(char *input);

/**** built-in ****/
int	ft_built_ins(char *input, char **envp);
void	ft_ctrl_c(int signal);

/**** commands functions ****/
int	get_cmd_size(char **input);
int	is_separator(char *str);
int	check_separator(char *str);
int	is_double_char(char *str);
int	what_separator(const char *separator);
int	is_pipe(const char *str);
int	count_pipe(char **input);
int	do_redirection(char **input, int *cmd_fd);
int	get_opt_size(char **input);
void	free_cmd_list(t_command *cmd_list, int size);
t_command	set_cmd(char **input, char *path);
void	launch_cmd(t_command *cmd_list, int cmd_amount);
void	execute_one_cmd(t_command command);
void	execute_multiple_cmd(t_command *command, int cmd_amount);
void	create_fork(t_command command, char **envp);

/**** redirections ****/
int	output_redir(int *cmd_output_fd, const char *filename);
int	output_append(int *cmd_output_fd, const char *filename);
int	input_redir(int *cmd_input_fd, const char *filename);
int	here_doc(int *infile, const char *input);
//void	output_redir(t_commands *commands);
//void	output_append(const char *filename, const char *text);

char	*error_msg(const char *filename);

#endif
