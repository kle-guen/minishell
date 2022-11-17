/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:22:13 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/17 18:05:54 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

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
	
	env_list = ft_create_env_list(envp);
	if (ac != 1)
		return (0);
	g_exit_status = 127;
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_ctrl_c);
	while (1)
	{
		input = readline("$> ");
		if (!input)
			break ;
		if (*input)
		{
			add_history(input);
			cmd_args = ft_parse_input(input, env_list);
			if (!(ft_strncmp(cmd_args[0], "exit", 5)))
			{
				if (cmd_args[1])
				{
					if (cmd_args[2] != NULL)
						ft_putstr_fd("minishell: exit: too many arguments\n", 2);
					else
					{	
						g_exit_status = ft_atoi(cmd_args[1]);					
						free_str_tab(cmd_args);
						break ;
					}
				}
				else
				{	
					free_str_tab(cmd_args);
					break ;
				}
			}
			else if (cmd_args[0])
				execute_input(cmd_args, &env_list);
			free(input);
			ft_free_tab(cmd_args);
		}
	}
	printf("exit\n");
	ft_free_env(&env_list);
	return (0);
}
