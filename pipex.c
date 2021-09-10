/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:33:40 by sachouam          #+#    #+#             */
/*   Updated: 2021/09/10 03:18:32 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void
	ft_print_and_free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		printf("%s\n", tab[i]);
		free(tab[i]);
	}
	free(tab);
}

static void
	ft_set_struc(t_prcs *process)
{
	process->fd = 0;
	process->id = 0;
	process->cmd = NULL;
}
/*
static void
	ft_first_fork(t_prcs *process1, int **pi, char **envp, char *arg)
{
	process1->fd = open(arg, O_RDONLY);
	close(pi[0]);
	dup2(pi[1], 1);
	if (process1->fd != -1)
	{
		dup2(process1->fd, 0);
		execve(process1->cmd[0], process1->cmd, envp);
	}
	perror("pipex");
	exit(0);
}

static int
	ft_second_fork(t_prcs *process2, int **pi, char **envp, char *arg)
{
	process2->fd = open(arg, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	close(pi[1]);
	dup2(pi[0], 0);
	if (process2->fd != -1)
	{
		dup2(process2->fd, 1);
		execve(process2->cmd[0], process2->cmd, envp);
	}
	perror("pipex");
	exit(0);
}
*/
int
	main(int ac, char **av, char **envp)
{
	int		pi[2];
	char	**path;
	t_prcs	process1;
	t_prcs	process2;

	ft_set_struc(&process1);
	ft_set_struc(&process2);
	if (ac != 5)
		return (0);
	path = ft_tab_of_paths(envp);
	if (!path)
		return (0);
	process1.cmd = ft_handling_command(av[2], path);
	process2.cmd = ft_handling_command(av[3], path);
	if (!process1.cmd || !process2.cmd)
		return (0);
	if (pipe(pi) == -1)
		return (0);
	process1.id = fork();
	if (process1.id < 0)
		return (0);
	if (process1.id == 0)
	{
		process1.fd = open(av[1], O_RDONLY);
		close(pi[0]);
		dup2(pi[1], 1);
		if (process1.fd != -1)
		{
			dup2(process1.fd, 0);
			execve(process1.cmd[0], process1.cmd, envp);
		}
		perror("pipex");
		exit(0);
	}
	else
	{
		process2.id = fork();
		if (process2.id < 0)
			return (0);
		if (process2.id == 0)
		{
			process2.fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 00644);
			close(pi[1]);
			dup2(pi[0], 0);
			if (process2.fd != -1)
			{
				dup2(process2.fd, 1);
				execve(process2.cmd[0], process2.cmd, envp);
			}
			perror("pipex");
			exit(0);
		}
		else
		{
			close(pi[0]);
			close(pi[1]);
			while (wait(NULL) != -1);
		}
	}
	ft_free_tab(process1.cmd);
	ft_free_tab(process2.cmd);
	ft_free_tab(path);
	return (0);
}
