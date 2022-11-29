/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 22:22:13 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/29 10:56:22 by kle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <limits.h>

int	g_exit_status;

void	execute_input(char **cmd_args, t_env **env_list)
{
	int	i;

	i = ft_built_ins(cmd_args, env_list);
	if (!i)
		ft_execute_cmd(cmd_args, *env_list);
}
int	ft_is_not_alpha(char *str)
{
	size_t	i;
	 
	i = 0;
	if (str == NULL)
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) && str[i])
		i++;
	if (i == ft_strlen(str))
		return (0);
	return (1);
}

int	ft_charcmp(char c, char cmp)
{
	if ((c - cmp) > 0)
		return (c - cmp);
	return (0);
}
int	is_too_large(char *str)
{
	size_t	size;
	int	i;
	char	*base;
	int	base_index;
	
	base_index = 0;
	i = 0;
	if (str == NULL)
		return (0);
	size = ft_strlen(str);
	if (size == 20)
		base = "-9223372036854775808";
	else
		base = "9223372036854775807";
	if (size > 20)
		return (1);
	else if (size == 20 || size == 19)
	{
		while (str[i])
		{
			if (ft_charcmp(str[i], base[base_index]) != 0)
				return (1);
			i++;
			base_index++;
		}
	}
	return (0);
}

void	ft_exit_built(t_command cmd, t_minishell *execution)
{
	int value;
	
	if (is_too_large(cmd.av[1]) == 1)
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		ft_free_execution(execution);
		exit (2);
	}
	if (ft_is_not_alpha(cmd.av[1]) == 1)
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		ft_free_execution(execution);
		exit (2);
	}
	if (cmd.av[1])
	{
		if (cmd.av[2] != NULL)
		{
			printf("exit\n");
			g_exit_status = 1;
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		}
		else
		{
			value = ft_atoi(cmd.av[1]);
			printf("exit\n");
			ft_free_execution(execution);
			exit(value);
		}
	}
	else
	{
		printf("exit\n");
		ft_free_execution(execution);
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
