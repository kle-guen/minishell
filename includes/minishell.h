/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:23:16 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/06 18:07:37 by kle-guen         ###   ########.fr       */
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
    int  is_printed;
    struct s_env *next;
}               t_env;

typedef struct	s_command
{
	char **av; 
	int  cmd_fd[2];
	char	*path;
}		t_command;

/**** parsing ****/

char	**ft_parse_input(char *input, t_env *env_list);

t_env   *ft_create_env_list(char **envp);
void	ft_print_env(t_env *env_list);
void	ft_print_export(t_env *env_list);
char	*ft_strjoin_sep(char *s1, char *s2);
void	ft_free_tab(char **tab);
void	ft_free_env(t_env **envp);
int     ft_is_close_quotes(char *str, char quote);
void	ft_match_key(char **key, int len, t_env *env_list);
char	*ft_replace_dollar(char *input, t_env *env_list , int *index, int *len);
char	*ft_realloc_key(char *str, char *key, int *len, int *index);
int	ft_strlen_key(char *str);
int     ft_strlen_key_plus(char *str);
int     ft_strlen_noquote(char *str);
int     ft_strlen_quote(char *str, char quote);
int     ft_strlen_redir(char *str, char redir);
int     ft_strlen_dollar(char *str);
char	*ft_get_key(char *str);
char	*ft_get_value(char *str);
t_env	*ft_laststack(t_env *env_list);
t_env	*ft_new_lst_env(char *envp);
t_env	*ft_last_lst_env(t_env *env_list);
void	ft_add_back_lst_env(t_env **env_list, t_env *new);
t_env   *ft_create_env_list(char **envp);
char	*ft_get_env(char *key, t_env *env_list);
void	ft_execute_cmd(char **cmd_args, t_env *env_list);

/**** find path ****/
char	*add_slash(char *str);
char	*find_path(char *command, char *path);
void	free_str_tab(char **tab_str);
char	*get_path(char *command, char *path);

//void	execute_cmd(char *input, char **envp);
pid_t	execute_cmd(t_command command, int *pipefd1, int *pipefd2);

/**** built-in ****/
int	ft_built_ins(char **cmd_args, t_env **env_list);
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
