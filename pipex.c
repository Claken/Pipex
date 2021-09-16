/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:33:40 by sachouam          #+#    #+#             */
/*   Updated: 2021/09/16 19:51:31 by sachouam         ###   ########.fr       */
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

void
	ft_set_struc(t_prcs *process)
{
	process->fd = 0;
	process->id = 0;
	process->cmd = NULL;
}

void
	ft_close_fdz(int pi[])
{
	close(pi[0]);
	close(pi[1]);
}

void
	ft_dup2_and_execve(int num, int pi[], char **envp, t_prcs *process)
{
	int numm;

	if (num == 0)
		numm = 1;
	if (num == 1)
		numm = 0;
	close(pi[num]);
	dup2(pi[numm], numm);
	if (process->fd != -1)
	{
		dup2(process->fd, num);
		execve(process->cmd[0], process->cmd, envp);
	}
	perror("pipex");
	exit(0);
}

int
	main(int ac, char **av, char **envp)
{
	int		pi[2];
	char	**path;
	t_prcs	process1;
	t_prcs	process2;
	pid_t	prowait;

	if (ac != 5)
		return (0);
	ft_set_struc(&process1);
	ft_set_struc(&process2);
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
		ft_dup2_and_execve(0, pi, envp, &process1);
	}
	else
	{
		process2.id = fork();
		if (process2.id < 0)
			return (0);
		if (process2.id == 0)
		{
			process2.fd = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 00644);
			ft_dup2_and_execve(1, pi, envp, &process2);
		}
		else
		{
			ft_close_fdz(pi);
			prowait = 0;
			while (prowait != -1)
				prowait = wait(NULL);
		}
	}
	ft_free_tab(process1.cmd);
	ft_free_tab(process2.cmd);
	ft_free_tab(path);
	return (0);
}
