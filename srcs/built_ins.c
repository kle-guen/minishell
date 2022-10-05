/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:31:52 by kle-guen          #+#    #+#             */
/*   Updated: 2022/10/05 17:37:17 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_ctrl_c(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	ft_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void	ft_pwd(void)
{
	char	*buff;
	size_t		i;

	i = 0;
	buff = malloc(sizeof(char));
	while (getcwd(buff, i) == NULL && i < 4294967294)
	{
		free(buff);
		buff = malloc(sizeof(char) + i * sizeof(char));
		i++;
	}
	printf("%s\n", buff);
}

void	ft_cd(char *path)
{
	chdir(path);
}

int	ft_built_ins(char *input, char **envp)
{
	if (!(ft_strncmp(input, "env", 3)))
		ft_env(envp);
	if (!(ft_strncmp(input, "pwd", 3)))
		ft_pwd();
	if (!(ft_strncmp(input, "cd", 2)))
		ft_cd(input + 3);
}