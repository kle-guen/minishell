/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chjoie <chjoie@student.42angouleme.fr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:49:30 by chjoie            #+#    #+#             */
/*   Updated: 2022/10/14 13:48:03 by chjoie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

int	main(int ac, char **av, char **envp)
{
	(void) ac;
	(void) av;
	(void) envp;
	char	*path[] = {"/usr/bin/cat", "/usr/bin/grep", "/usr/bin/wc" , "/usr/bin/wc"};
	char	*cmd1[] = {"cat", "test1", NULL};
	char	*cmd2[] = {"grep", "u", NULL};
	char	*cmd3[] = {"wc", "-l", NULL};
	char	*cmd4[] = {"wc", "-l", NULL};
	
	char	**pipe_cmd[] = {cmd1, cmd2, cmd3, cmd4, NULL};
	
	int	pipefd[2];
	pid_t	pid;
	int	savefd;

	savefd = 0;
	(void) ac;
	(void) av;
	int 	x = 0;	
	while (pipe_cmd[x] != NULL)
	{
		printf("x = %d\n", x);
		if (pipe(pipefd) == -1)
			printf("error\n");
		pid = fork();
		if (pid == 0)
		{
			dup2(savefd, 0);
			if (pipe_cmd[x + 1] != NULL)
				dup2(pipefd[1], 1);
			close(pipefd[0]);
			execve(path[x], pipe_cmd[x], envp);		
		}
		else
		{
			wait(NULL);
		//	close(savefd);
			close(pipefd[1]);
			savefd = pipefd[0];
			//close(old_fd);
			x++;
		}
	}
	// voir si utiliser la fonction unlink sert a quelque chose ?
	return (0);
}
