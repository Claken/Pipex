/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 01:23:17 by sachouam          #+#    #+#             */
/*   Updated: 2021/08/06 19:54:42 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int
	ft_close_fdz(int *fd1, int *fd2)
{
	close(*fd1);
	close(*fd2);
	return (0);
}
int
	main(int ac, char **av, char **envp)
{
	int		fd1;
	int		fd2;
	int		fd3[2];
	pid_t	procid;
	// fd pour le pipe :
	// - fd[0] = pour read dans le pipe
	// - fd[1] = pour write dans le pipe
	// quand tu read, tu vides le fd3

	if (ac != 5)
		return (0);
	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[4], O_RDONLY);
	if (pipe(fd3) == -1)
		return (ft_close_fdz(&fd1, &fd2));
	procid = fork();
	if (procid == -1)
		return (ft_close_fdz(&fd1, &fd2));
	if (procid == 0)
	{
		printf("child\n");
		printf("fd1 = %d\nfd2 = %d\n", fd1, fd2);
	}
	else
	{
		wait(NULL);
		printf("parent\n");
	}
	if (fd1 == -1)
	{

	}
	if (fd2 == -1)
	{
		fd2 = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 00644);
		if (fd2 == -1)
		{
			printf("fd2 %d\n", fd2);
			return (ft_close_fdz(&fd1, &fd2));
		}
	}
	printf("nice\n\n");
	return (ft_close_fdz(&fd1, &fd2));
}
