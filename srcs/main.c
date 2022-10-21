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

void	init_commands(t_cmd_opt *commands, char **parsed_input)
{
	commands->cmd_line = get_commands(parsed_input);
	//commands.cmd1 = fctn
	commands->opt = 0;
	commands->next_opt = 0;
	commands->cmd_infile; //void pour remplacer par cmd_fd[2]
	commands->cmd_outfile;
}

void	execute_input(char **parsed_input, char **envp)
{
	int	i;
	t_cmd_opt commands;

	init_commands(commands);
	i = ft_built_ins(parsed_input, envp); //modif cette fonction et la lancer + le if dans execute_cmd pour qu'on puisse combiner les builtins avec les | < > etc...
	if (!i)
	{
		while (next_opt != NULL)
			execute_cmd(commands.cmd_line, envp);
	}
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	char	**parsed_input;
	
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
		if (!(ft_strncmp(input, "exit", 4)))
			break ;
		add_history(input);
		parsed_input = ft_parse_input(input);
		free(input);
		execute_input(parsed_input, envp);
		//free(parsed_input)
		input = NULL;
	}
	free(input);
	printf("exit\n");
	return (0);
}
