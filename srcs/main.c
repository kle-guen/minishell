/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:22:13 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/23 10:01:50 by kle-guen         ###   ########.fr       */
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

void	ft_exit(char **cmd, t_env *env_list)
{
	int value;
	
	value = 0;
	if (cmd[1])
	{
		if (cmd[2] != NULL)
		{
			printf("exit\n");
			g_exit_status = 1;
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		}
		else
		{	
			value = ft_atoi(cmd[1]);
			printf("exit\n");
			ft_free_env(&env_list);	
			free_str_tab(cmd);
			exit(value);
		}
	}
	else
	{
		printf("exit\n");
		ft_free_env(&env_list);
		free_str_tab(cmd);
		exit(0);
	}
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
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_ctrl_c);
	g_exit_status = 0;
	while (1)
	{
		input = readline("$> ");
		if (!input)
		{
			ft_free_env(&env_list);
			break;
		}
		if (*input)
		{
			add_history(input);
			cmd_args = ft_parse_input(input, env_list);
			if (cmd_args[0] && ft_verif_parsing(cmd_args))
			{
				if (!(ft_strncmp(cmd_args[0], "exit", 5)))
					ft_exit(cmd_args, env_list);
				else
					execute_input(cmd_args, &env_list);
			}
			free(input);
			ft_free_tab(cmd_args);
		}
	}
	printf("exit\n");
	ft_free_env(&env_list);
	return (0);
}
