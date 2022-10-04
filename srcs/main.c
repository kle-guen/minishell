/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:22:13 by kle-guen          #+#    #+#             */
/*   Updated: 2022/10/04 13:45:11 by chjoie           ###   ########.fr       */
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

char	*parse_input(char *input)
{
	char	*parsed;

	parsed = input;
	return (parsed);
}

void	execute_input(char *input, char **envp)
{
	if (!(ft_strncmp(input, "env", 3)))
		ft_env(envp);
	else if (!(ft_strncmp(input, "pwd", 3)))
		ft_pwd();
	else if (!(ft_strncmp(input, "cd", 2)))
		ft_cd(input + 3);
	else
		execute_cmd(input, envp);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;

	(void) av;
	(void) envp;
	if (ac == 1)
	{
		while (1)
		{
			input = readline("$> ");
			if (!input)
				break ;
			add_history(input);
			input = parse_input(input);
			if (!(ft_strncmp(input, "exit", 4)))
				break ;
			execute_input(input, envp);
		}
	}
	printf("exit\n");
	return (0);
}
