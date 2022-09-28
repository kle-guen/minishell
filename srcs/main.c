/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:22:13 by kle-guen          #+#    #+#             */
/*   Updated: 2022/09/29 00:17:22 by kle-guen         ###   ########.fr       */
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

int	main(int ac, char **av, char **envp)
{
	char	*input;

	(void)envp;
	(void)ac;
	(void)av;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_ctrl_c);
	while (1)
	{
		input = readline("$> ");
		if (!input)
			break ;
		if (!(ft_strncmp(input, "env", 3)))
			ft_env(envp);
		if (!(ft_strncmp(input, "pwd", 3)))
			ft_pwd();
		if (!(ft_strncmp(input, "cd", 2)))
			ft_cd(input + 3);
		if (!(ft_strncmp(input, "exit", 4)))
			break ;
		add_history(input);
	}
	printf("exit\n");
	return (0);
}
