/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:57:05 by chjoie            #+#    #+#             */
/*   Updated: 2022/11/01 10:57:05 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft.h"

char	*error_msg(const char *filename)
{
	char *error_msg;
	
	error_msg = ft_strjoin("msh: ", filename);
	return (error_msg);  
}
