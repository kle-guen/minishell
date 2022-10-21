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
# include "libft.h"

typedef struct s_env
{
    char *key;
    char *value;
}               t_env;

typedef struct	s_cmd_opt
{
	char ***cmd_line;
	char **cmd1;
	char **cmd2; // besoin des deux ?
	int  cmd_infile;
	int  cmd_outfile;
	int  opt;
	int  next_opt;
}		t_cmd_opt;

char	*add_slash(char *str);
char	*find_path(char *command, char *path);
void	free_str_tab(char **tab_str);
char	*get_path(char *command, char *path);
void	execute_cmd(char *input, char **envp);
int     *ft_input_map(char *input);
char	*ft_parse_input(char *input);
int	ft_built_ins(char *input, char **envp);
void	ft_ctrl_c(int signal);
char	***get_commands(char **input);
int	get_cmd_size(char **input);
int	is_separator(char *str);
int	check_separator(char *str);
int	is_double_char(char *str);

#endif
