/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:22:13 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/06 18:07:07 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute_input(char **cmd_args, t_env **env_list)
{
	int	i;
	
	i = ft_built_ins(cmd_args, env_list);
	if (!i)
		ft_execute_cmd(cmd_args, *env_list);
}

int	main(int ac, char **av, char **envp)
{
	char	*input;
	t_env *env_list;
	char	**cmd_args;
	(void) av;
	(void) envp;
	env_list = ft_create_env_list(envp);
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
		cmd_args = ft_parse_input(input, env_list);
		//ft_free_tab(cmd_args);
		if (!(ft_strncmp(input, "exit", 4)))
			break ;
		execute_input(cmd_args, &env_list);
		free(input);
	}
	printf("exit\n");
	ft_free_env(&env_list);
	return (0);
}

/*
int	main(int ac, char **av, char **envp)
{
	char	*input = malloc(sizeof(char) * 8);
	char	**cmd_args;
	t_env *env_list;

	(void) envp;
	(void)av;
	(void)ac;
	input[0] = '"';
	input[1] = '$';
	input[2] = 'U';
	input[3] = 'S';
	input[4] = 'E';
	input[5] = 'R';
	input[6] = '"';
	input[7] = '\0';
	env_list = ft_create_env_list(envp);
	//if (ac != 2)
	//	return (0);
	cmd_args = ft_parse_input(input, env_list);
	ft_free_tab(cmd_args);
	ft_free_env(&env_list);
	return(0);
}
*/
