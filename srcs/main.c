/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:22:13 by kle-guen          #+#    #+#             */
/*   Updated: 2022/10/04 19:54:25 by kle-guen         ###   ########.fr       */
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

void	print_tab(int *tab, char *input, int size)
{
	int	i;

	i = 0;
	printf("Size = %d\n", size);
	printf("Input = %s\n", input);
	printf("Input map =");
	while (i < size)
	{
		printf(" %d", tab[i]);
		i++;
	}
	printf("\n");
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
		if (!(ft_strncmp(input, "map", 3)))
		{
			//printf("%ld\n", ft_strlen(input) - 4);	
			//print_tab(ft_input_map(input + 4), input, ft_strlen(input) - 4);
			printf("%s\n", ft_parse_input(input + 4));
		}
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
