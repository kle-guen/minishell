/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:23:16 by kle-guen          #+#    #+#             */
/*   Updated: 2022/12/08 10:51:16 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include "libft.h"

extern int	g_exit_status;

typedef struct s_env
{
	char			*key;
	char			*value;
	int				is_printed;
	struct s_env	*next;
}				t_env;

typedef struct s_cmd
{
	char	**av;
	int		cmd_fd[2];
	char	*path;
}		t_cmd;

typedef struct s_exec
{
	t_cmd	*cmd_list;
	pid_t	*child_id;
	t_env	*env;
	int		cmd_total;
	char	**env_str;
	char	**input;
}		t_exec;

/**** parsing ****/

char	**ft_parse_input(char *input, t_env *env_list);
char	*ft_no_quotes(char *input, t_env *env_list, int *index);
char	*ft_single_quotes(char *input, int *index, char prev);
char	*ft_double_quotes(char *input, t_env *env_list, int *index, char prev);
t_env	*ft_create_env_list(char **envp);
void	ft_print_env(t_env *env_list);
void	ft_print_export(t_env *env_list);
char	*ft_strjoin_sep(char *s1, char *s2);
void	ft_free_tab(char **tab);
void	ft_free_env_var(t_env *env_var);
void	ft_free_env(t_env **envp);
void	ft_dfree(char *s1, char *s2);
int		ft_is_close_quotes(char *str, char quote);
void	ft_match_key(char **key, int len, t_env *env_list);
char	*ft_replace_dollar(char *input, t_env *env_list, int *index, int *len);
char	*ft_realloc_key(char *str, char *key, int *len, int *index);
int		ft_strlen_key(char *str);
int		ft_strlen_key_plus(char *str);
int		ft_strlen_noquote(char *str);
int		ft_strlen_quote(char *str, char quote);
int		ft_strlen_redir(char *str, char redir);
int		ft_strlen_dollar(char *str);
char	*ft_get_key(char *str);
char	*ft_get_value(char *str);
t_env	*ft_laststack(t_env *env_list);
t_env	*ft_new_lst_env(char *envp);
t_env	*ft_last_lst_env(t_env *env_list);
void	ft_add_back_lst_env(t_env **env_list, t_env *new);
t_env	*ft_create_env_list(char **envp);
char	*ft_get_env(char *key, t_env *env_list);
char	*ft_strjoin_dfree(char *s1, char *s2);
int		ft_verif_parsing(char **cmd_args);
char	*ft_keep_quotes(char *input, int *index, char quote);
char	*ft_empty_string(int *index);
char	*ft_remove_single_quotes(char *input, int *index);
char	*ft_double_quotes_closed(char *input, int *index, t_env *env_list);
char	*ft_double_quotes_unclosed(char *input, int *index);
char	*ft_no_quotes_no_dollar(char *input, int *index, int *index_str);
void	ft_redir_and_pipe(char *input, char **clean_input, int *index);

/**** find path ****/

char	*add_slash(char *str);
char	*find_path(char *command, char *path);
void	free_str_tab(char **tab_str);
char	*get_path(char *command, char *path);
int		check_directory_error(char *command);

/**** setup command structure ****/

void	ft_execution(char **cmd_args, t_env *env_list);
pid_t	execute_cmd(t_exec *execution, int *pipefd1, int *pipefd2, \
int cmd_nb);
void	init_exec_structure(t_exec *execution, char **cmd_args, \
t_env *env_list);
int		check_directory(char *command);

/**** built-in ****/

void	ft_env(t_env *env_list);
void	ft_pwd(void);
void	ft_cd(char *path, t_env *env_list);
void	ft_export(t_env *env_list, char **cmd_args);
void	ft_unset(t_env **env_list, char **cmd_args);
int		ft_built_ins_pipe(char **cmd_args, t_env **env_list);
int		ft_is_built_ins(char *cmd);
int		ft_built_ins(char **cmd_args, t_env **env_list);
void	ft_launch_cd(char **cmd_args, t_env **env_list);
void	ft_lauch_echo(char **cmd_args);
void	ft_ctrl_c(int signal);
char	*ft_get_cwd(void);
char	*ft_get_env(char *key, t_env *env_list);
int		ft_key_has_value(char *new_env);
void	ft_join_key_value(t_env *env_list, char *key, char *value);
char	*ft_remove_plus(char *arg);
int		ft_key_is_in_env(t_env *env_list, char *key);
void	ft_plus_equal_export(t_env *env_list, char *arg);
void	ft_replace_env_value(t_env *env_list, char *key, char *value);
void	ft_add_env(t_env *env_list, char *arg);
void	ft_remove_env(t_env **env_list, char *arg, int len_key, t_env *tmp);
int		ft_echo_flag(char *str);
void	ft_change_pwd(t_env *env_list, char *old_pwd);
void	ft_exit(char **cmd, t_env *env_list);
void	ft_exit_built(t_cmd cmd, t_exec *execution);
int		ft_contain_pipe_or_redir(char **cmd_args);
void	ft_reparsing(char **cmd_args);
int		get_env_size(t_env **root);
char	**get_exec_env(t_env **root);
void	ft_echo_no_nl(char **cmd_args);

/**** commands functions ****/

int		check_after_parsing(char **input);
int		is_unclosed(char *str);
int		get_cmd_size(char **input);
int		is_separator(char *str);
int		check_next_str(char **input);
int		check_separator(char *str);
int		check_input(char *str);
int		is_double_char(char *str);
int		what_separator(const char *separator);
int		is_pipe(const char *str);
int		count_pipe(char **input);
int		get_opt_size(char **input);
void	free_cmd_list(t_cmd *cmd_list, int size);

/**** fill commands ****/

t_cmd	set_cmd(char **input, char *path);
t_exec	init_execution_structure(char **cmd_args, t_env *env_list);
char	**get_cmd_opt(char **input);
void	fill_cmds(t_exec *execution, char *path, char **input);
t_cmd	set_cmd(char **input, char *path);
int		check_here_doc(char **cmd_args, t_env *env_list);
void	launch_cmd(t_exec *execution);
void	execute_one_cmd(t_exec *execution);
void	execute_multiple_cmd(t_exec *execution);
pid_t	create_fork(t_exec *command);
void	close_fd(t_cmd *cmd_list, int cmd_amount);
void	ft_free_execution(t_exec *execution);

/**** redirections ****/

int		do_redirection(char **input, int *cmd_fd, int check);
int		output_redir(int *cmd_output_fd, const char *filename);
int		output_append(int *cmd_output_fd, const char *filename);
int		input_redir(int *cmd_input_fd, const char *filename);

/**** here doc ****/

void	here_doc(char *delimiter, char **cmd_args, t_env *env_list, int fd);
int		here_doc_redir(int *cmd_input_fd);
void	ctrl_here(int signal);
void	ft_free_here_doc(char *line, char *delimiter, int fd, int code);
void	launch_here_doc(char **cmd_args, t_env *env_list, int fd, int x);
void	close_here_doc(int fd);
void	clear_here_doc(void);

/**** error message ****/

char	*error_msg(const char *filename);
void	print_here_doc_error(char *delimiter);
void	print_syntax_error(void);

/**** execution ****/

char	**get_exec_env(t_env **root);
void	setup_middle_command(int *fd_in, int *fd_out, int *pipe1, int *pipe2);
void	setup_first_cmd(int *fd_in, int *fd_out, int *pipefd);
void	setup_last_cmd(int *fd_in, int *fd_out, int *pipefd);
void	set_infile(int *cmd_infile, int *pipefd);
void	set_outfile(int *cmd_outfile, int *pipefd);
pid_t	cmd_not_found1(t_exec *execution, int cmd_nb, int *pipefd1);
pid_t	not_found2(t_exec *execution, int cmd_nb, int *pipe1, int *pipe2);
pid_t	cmd_not_found3(t_exec *execution, int cmd_nb, int *pipefd);
void	print_not_found(char *cmd_name);
void	one_command_not_found(char	*cmd_name);
void	close_pipe(int *pipefd);
void	execute(t_exec *execution, int cmd_nb);
void	execute_in_fork(t_exec *execution, int *pipefd1, int cmd_nb);
void	wait_child(pid_t *child_id, int cmd_amount);
void	ft_if_after_buitin(t_exec *execution, int cmd_nb);
void	child_last_cmd(t_exec *execution, int *pipefd, int cmd_nb);

#endif
