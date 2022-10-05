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
# include <signal.h>
# include "libft.h"

typedef struct s_env
{
    char *key;
    char *value;
}               t_env;

int     *ft_input_map(char *input);
char	*ft_parse_input(char *input);
void	ft_built_ins(char *input);
void	ft_ctrl_c(int signal);

#endif