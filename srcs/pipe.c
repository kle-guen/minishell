/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:49:30 by chjoie            #+#    #+#             */
/*   Updated: 2022/10/13 13:15:22 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"
#include "../includes/libft.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	has_pipe(char *str)
{
	int has_pipe;
	int	x;
	
	has_pipe = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == '|')
			has_pipe = 1;
		x++;
	}
	return (has_pipe);
}
/*
void	exe_one_pipe(char *cmd, int fd[2], char **envp)
{
	char **command;
	char	*path;
	pid_t cpid;

	command = ft_split(cmd, ' ');
	path = get_path(command[0], getenv("PATH"));
	cpid = fork();
//	printf("path = %s\n", path);
	if (cpid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		execve(path, command, envp);
	}
//	else
		waitpid(cpid, NULL, 0);
}
*/
void	execute_pipe(char **cmd_line, char **envp)
{
	int	pipefd[2];
	int	pipefd1[2];
//	int	x;

	cmd_line++;

//	x = 0;
	pid_t	cpid;
	pid_t	cpid2;

	char	**test = malloc(sizeof(char *) * 3);
	test[0] = "cat";
	test[1] = "test1";
	test[2] = NULL;

	if (pipe(pipefd) == -1)
		printf("error");
	if (pipe(pipefd1) == -1)
		printf("error");
//	printf("%s\n", cmd_line[0]);
/*	while (cmd_line[x] != NULL)
	{
		exe_one_pipe(cmd_line[x], pipefd, envp);
		x++;
	}*/
	cpid = fork();
	if (cpid == 0)
	{
		close(pipefd1[0]);
		close(pipefd1[1]);
		close(pipefd[0]);


		printf("fd de de lecture = standart\n");
		printf("fd de d'ecriture = %d (pipefd[1])\n\n", pipefd[1]);

		dup2(pipefd[1], 1);
//		close(pipefd[1]);
		execve("/usr/bin/cat", test, envp);
	}
	else
		waitpid(cpid, NULL, 0);
	cpid2 = fork();
	if (cpid2 == 0)
	{
		char	**test2 = malloc(sizeof(char *) * 3);
		test2[0] = "grep";
		test2[1] = "u";
		test2[2] = NULL;
		close(pipefd[1]);
		close(pipefd1[0]);
		dup2(pipefd[0], 0);
		printf("fd de de lecture = %d(pipefd[0])\n", pipefd[0]);
		printf("fd de d'ecriture = %d(pipefd1[1])\n\n", pipefd1[1]);
		dup2(pipefd1[1], 1);
//		close(pipefd[0]);
//		close(pipefd1[1]);
		execve("/usr/bin/grep", test2, envp);
	}
	else
		waitpid(cpid2, NULL, 0);
	pid_t cpid3 = fork();
	if (cpid3 == 0)
	{
		char	**test3 = malloc(sizeof(char *) * 3);
		test3[0] = "wc";
		test3[1] = "-l";
		test3[2] = NULL;
		close(pipefd[0]);
//		close(pipefd[1]);
		printf("fd de de lecture = %d(pipefd1[0])\n", pipefd1[0]);
		printf("fd de d'ecriture = %d(pipefd[1])\n\n", pipefd[1]);
		dup2(pipefd[1], 1);
		dup2(pipefd1[0], 0);
//		close(pipefd[1]);
//		close(pipefd1[0]);
		close(pipefd1[1]);
		execve("/usr/bin/wc", test3, envp);
	}
	else
		waitpid(cpid3, NULL, 0);
	pid_t cpid4 = fork();
	if (cpid4 == 0)
	{
		char	**test3 = malloc(sizeof(char *) * 3);
		test3[0] = "wc";
		test3[1] = "-l";
		test3[2] = NULL;
//		close(pipefd[0]);
		close(pipefd[1]);

		printf("fd de d'ecriture = standart\n");
		printf("fd de de lecture = %d(pipefd[0])\n\n", pipefd[0]);
		dup2(pipefd[0], 0);
		close(pipefd1[0]);
//		close(pipefd[0]);
		close(pipefd1[1]);
		execve("/usr/bin/wc", test3, envp);
	}
	else
		waitpid(cpid4, NULL, 0);
//	else
//	{
	close(pipefd[0]);
	close(pipefd[1]);
	close(pipefd1[0]);
	close(pipefd1[1]);
//	while (wait(NULL) != -1)
//	{
//		printf("waited\n");
//	}
	
}


int	main(int ac, char **av, char **envp)
{
	char	**pipe_cmd;

	if (ac != 2)
		return (1);
//	if (has_pipe(av[1]))
	pipe_cmd = ft_split(av[1], '|');

	execute_pipe(pipe_cmd, envp);
	free(pipe_cmd);
	return (0);
}
