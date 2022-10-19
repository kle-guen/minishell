/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:22:13 by kle-guen          #+#    #+#             */
/*   Updated: 2022/10/05 17:37:26 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_input(char *input, char **envp)
{
	int	i;
	
	i = ft_built_ins(input, envp);
	if (!i)
		execute_cmd(input, envp);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;

	(void) av;
	(void) envp;
	if (ac != 1)
		return (0);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_ctrl_c);
	while (1)
	{
		input = readline("$> ");
		if (!input)
			break ;
		add_history(input);
		input = ft_parse_input(input);
		if (!(ft_strncmp(input, "exit", 4)))
			break ;
		execute_input(input, envp);
		free(input);
		input = NULL;
	}
	free(input);
	printf("exit\n");
	return (0);
}
