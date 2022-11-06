/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-guen <kle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 17:31:52 by kle-guen          #+#    #+#             */
/*   Updated: 2022/11/06 17:52:24 by kle-guen         ###   ########.fr       */
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

void	ft_env(t_env *env_list)
{
	ft_print_env(env_list);
}
#include <limits.h>
char	*ft_get_cwd(void)
{
	char	*buff;
	size_t		i;

	i = 0;
	buff = malloc(sizeof(char));
	while (getcwd(buff, i) == NULL && i < UINT_MAX)
	{
		free(buff);
		buff = malloc(sizeof(char) + i * sizeof(char));
		i++;
	}
	return (buff);
}

void	ft_pwd(void)
{
	char	*buff;

	buff = ft_get_cwd();
	printf("%s\n", buff);
	free(buff);
}

char	*ft_get_env(char *key, t_env *env_list)
{
	t_env	*tmp;
	int		len_key;
	char	*value;

	len_key = ft_strlen(key);
	tmp = env_list;
	while (env_list)
	{
		if (!(strncmp(key, env_list->key, len_key)))
		{
			value = env_list->value;
			break ;
		}
		env_list = env_list->next;
	}
	env_list = tmp;
	return (value);
}

void	ft_change_pwd(t_env *env_list, char *old_pwd)
{
	t_env	*tmp;

	tmp = env_list;
	while (env_list)
	{
		if (!(strncmp("PWD", env_list->key, 3)))
		{
			free(env_list->value);
			env_list->value = ft_get_cwd();
		}
		env_list = env_list->next;
	}
	env_list = tmp;
	while (env_list)
	{
		if (!(strncmp("OLDPWD", env_list->key, 7)))
		{
			free(env_list->value);
			env_list->value = old_pwd;
		}
		env_list = env_list->next;
	}
	env_list = tmp;
}

void	ft_cd(char *path, t_env *env_list)
{
	int		i;
	char	*pwd;

	pwd = ft_get_cwd();
	i = chdir(path);
	if (i == -1)
	{
		printf("minishell: cd: %s: %s\n", path, strerror(errno));
		free(pwd);
	}
	else
		ft_change_pwd(env_list, pwd);
}

int	ft_key_has_value(char *new_env)
{
	int	i;

	i = 0;
	while (new_env[i])
	{
		if (new_env[i] == '=')
		{
			return (2);
		}
		else if (new_env[i] == '+' && new_env[i + 1] == '=')
		{
			return (3);
		}
		else if ((new_env[i] == '+' && new_env[i + 1] != '=') || (!(ft_isalnum(new_env[i]))))
		{
			return (1);
		}
		i++;
	}
	return (0);
}
/*
t_env	*ft_new_env_export(char *arg)
{
	t_env	*elem;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->key = ft_get_key(arg);
	elem->value = ft_get_value(arg);
	elem->next = NULL;
	return (elem);
}
*/
int		ft_key_is_in_env(t_env *env_list, char *key)
{
	int		len_key;
	t_env	*tmp;

	tmp = env_list;
	len_key = ft_strlen(key);
	while (env_list)
	{
		if (!(strncmp(env_list->key, key, len_key)) && (int)ft_strlen(env_list->key) == len_key)
			return (1);
		env_list = env_list->next;
	}
	env_list = tmp;
	return (0);
}

void	ft_join_key_value(t_env *env_list, char *key, char *value)
{
	t_env	*tmp;
	int		len_key;
	
	len_key = ft_strlen(key);
	tmp = env_list;
	while (env_list)
	{
		if (!(strncmp(env_list->key, key, len_key)) && (int)ft_strlen(env_list->key) == len_key)
			break;
		env_list = env_list->next;
	}
	if (!env_list->value)
		env_list->value = ft_calloc(1, sizeof(char));
	env_list->value = ft_strjoin(env_list->value, value);
	env_list = tmp;
}

void	ft_remove_plus(char *arg)
{
	char	*cpy;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cpy = ft_strdup(arg);
	free(arg);
	arg = malloc(sizeof(char) * ft_strlen(cpy));
	while (cpy[i])
	{
		if (cpy[i] != '+')
		{
			arg[j] = cpy[i];
			j++;
		}
		i++;

	}
	arg[j] = '\0';
}

void	ft_plus_equal_export(t_env *env_list, char *arg)
{
	char	*key;
	char	*value;
	int		i;

	i = 0;
	key = malloc(sizeof(char) * (ft_strlen_key_plus(arg) + 1));
	value = ft_get_value(arg);
	while (arg[i] != '+')
	{
		key[i] = arg[i];
		i++;
	}
	key[i] = '\0';
	if (ft_key_is_in_env(env_list, key))
	{
		ft_join_key_value(env_list, key, value);
	}
	else
	{
		ft_remove_plus(arg);
		ft_add_back_lst_env(&env_list, ft_new_lst_env(arg));
	}
}

void	ft_replace_env_value(t_env *env_list, char *key, char *value)
{
	t_env	*tmp;
	int		len_key;

	len_key = ft_strlen(key);
	tmp = env_list;
	while (env_list)
	{
		if (!(strncmp(env_list->key, key, len_key)) && (int)ft_strlen(env_list->key) == len_key)
			break;
		env_list = env_list->next;
	}
	free(env_list->value);
	env_list->value = value;
	env_list = tmp;
}

void	ft_add_env(t_env *env_list, char *arg)
{
	if (ft_key_has_value(arg) == 1)
	{
		ft_putstr_fd("minishell: export: `", 1); 
		ft_putstr_fd(arg, 1);
		ft_putstr_fd("': not a valid indentifier\n", 1);
	}
	else if (ft_key_has_value(arg) == 2)
	{
		if (!(ft_key_is_in_env(env_list, ft_get_key(arg))))
			ft_add_back_lst_env(&env_list, ft_new_lst_env(arg));
		else
			ft_replace_env_value(env_list, ft_get_key(arg), ft_get_value(arg));
	}
	else if (ft_key_has_value(arg) == 3)
	{
		ft_plus_equal_export(env_list, arg);
	}
	else
		if (!(ft_key_is_in_env(env_list, ft_get_key(arg))))
			ft_add_back_lst_env(&env_list, ft_new_lst_env(arg));
}

void	ft_remove_env(t_env **env_list, char *arg)
{
	t_env	*tmp;
	t_env	*tmp2;
	int		len_key;

	len_key = ft_strlen(arg);
	tmp = *env_list;
	if (!(strncmp((*env_list)->key, arg, len_key)) && (int)ft_strlen((*env_list)->key) == len_key)
	{
		/*printf("key = %s\n", env_list->key);
		printf("arg = %s\n", arg);
		printf("len_key = %d\n", (int)ft_strlen(env_list->key));
		printf("len_key = %d\n",len_key);*/
		tmp2 = *env_list;
		*env_list = (*env_list)->next;
		free(tmp2);
		return ;
	}
	else
	{
		while ((*env_list)->next)
		{
			if (!(strncmp((*env_list)->next->key, arg, len_key)) && (int)ft_strlen((*env_list)->next->key) == len_key)
			{
				tmp2 = (*env_list)->next;
				(*env_list)->next = tmp2->next;
				free(tmp2);
				break ;
			}
			*env_list = (*env_list)->next;
		}
	}
	*env_list = tmp;
}

void	ft_export(t_env *env_list, char **cmd_args)
{
	int		i;

	i = 0;
	while (cmd_args[i])
	{
		ft_add_env(env_list, cmd_args[i]);
		i++;
	}
	if (!i)
		ft_print_export(env_list);
}

void	ft_unset(t_env **env_list, char **cmd_args)
{
	int		i;

	i = 0;
	while (cmd_args[i])
	{
		ft_remove_env(env_list, cmd_args[i]);
		i++;
	}
}

int	ft_built_ins(char **cmd_args, t_env **env_list)
{
	if (!(ft_strncmp(cmd_args[0], "env", 3)))
	{
		ft_env(*env_list);
		return (1);
	}
	if (!(ft_strncmp(cmd_args[0], "export", 3)))
	{
		ft_export(*env_list, &cmd_args[1]);
		return (1);
	}
	if (!(ft_strncmp(cmd_args[0], "unset", 5)))
	{
		ft_unset(env_list, &cmd_args[1]);
		return (1);
	}
	if (!(ft_strncmp(cmd_args[0], "pwd", 3)))
	{
		ft_pwd();
		return (1);
	}
	if (!(ft_strncmp(cmd_args[0], "cd", 2)))
	{
		if (!cmd_args[1])
		{
			ft_cd(ft_get_env("HOME", *env_list), *env_list);  //getenv de HOME
			return (1);
		}
		else if (cmd_args[2])
		{
			ft_putstr_fd("minishell: cd: too many arguments\n", 2);
			return (1);
		}
		else
			ft_cd(cmd_args[1] , *env_list);
		return (1);
	}
	return (0);
}
