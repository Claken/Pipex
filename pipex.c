/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:33:40 by sachouam          #+#    #+#             */
/*   Updated: 2021/09/10 01:46:47 by sachouam         ###   ########.fr       */
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
	ft_close_fdz(int *fd1, int *fd2)
{
	close(*fd1);
	close(*fd2);
}

int
	main(int ac, char **av, char **envp)
{
	pid_t	procid;
	pid_t	procid2;
	int		pi[2];
	int		fd1;
	int		fd2;
	char	**cmd1;
	char	**cmd2;
	char	**path;

	if (ac != 5)
		return (0);
	path = ft_tab_of_paths(envp);
	if (!path)
		return (0);
	cmd1 = ft_handling_command(av[2], path);
	cmd2 = ft_handling_command(av[3], path);
	if (!cmd1 || !cmd2)
		return (0);
	if (pipe(pi) == -1)
		return (0);
	procid = fork();
	if (procid < 0)
		return (0);
	if (procid == 0)
	{
		fd1 = open(av[1], O_RDONLY);
		close(pi[0]);
		dup2(pi[1], 1);
		if (fd1 != -1)
		{
			dup2(fd1, 0);
			execve(cmd1[0], cmd1, envp);
		}
		perror("pipex");
		exit(0);
	}
	else
	{
		procid2 = fork();
		if (procid2 < 0)
			return (0);
		if (procid2 == 0)
		{
			fd2 = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 00644);
			close(pi[1]);
			dup2(pi[0], 0);
			if (fd2 != -1)
			{
				dup2(fd2, 1);
				execve(cmd2[0], cmd2, envp);
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
	ft_free_tab(cmd1);
	ft_free_tab(cmd2);
	ft_free_tab(path);
	return (0);
}
