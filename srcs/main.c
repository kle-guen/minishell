/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:22:13 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/30 16:45:50 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	g_exit_status;

void	execute_input(char **cmd_args, t_env **env_list)
{
	int	i;

	if (ft_is_built_ins(cmd_args[0]))
		g_exit_status = 0;
	i = ft_built_ins(cmd_args, env_list);
	if (!i)
		ft_execute_cmd(cmd_args, *env_list);
}

void	launch_minishell(char **envp)
{
	char	*input;
	t_env	*env_list;
	char	**cmd_args;

	env_list = ft_create_env_list(envp);
	while (1)
	{
		input = readline("$> ");
		if (!input)
		{
			ft_free_env(&env_list);
			break ;
		}
		if (*input)
		{
			add_history(input);
			cmd_args = ft_parse_input(input, env_list);
			if (cmd_args[0] && ft_verif_parsing(cmd_args))
				execute_input(cmd_args, &env_list);
			free(input);
			ft_free_tab(cmd_args);
		}
	}
	printf("exit\n");
	ft_free_env(&env_list);
}

int	main(int ac, char **av, char **envp)
{
	(void) av;
	if (ac != 1)
		return (0);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, ft_ctrl_c);
	g_exit_status = 0;
	launch_minishell(envp);
	return (0);
}
