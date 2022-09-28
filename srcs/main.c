/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:22:13 by kle-guen          #+#    #+#             */
/*   Updated: 2022/09/28 16:40:43 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	parse_input(char *input)
{
	
	return (1);
}

int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*tab[3];

	tab[0] = "ls";
	tab[1] = "-la";
	tab[2] = NULL;

	(void) ac;
	(void) av;
	//execve("/usr/bin/ls", tab, env);
	while (1)
	{
		input = readline("$> ");
		if (!input)
			break ;
		add_history(input);

		execve("/usr/bin/ls", tab, env);
		
	//	parse_input(input);
	}
	printf("exit\n");
	return (0);
}
