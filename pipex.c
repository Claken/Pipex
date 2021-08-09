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

void
	ft_close_fdz(int *fd1, int *fd2)
{
	close(*fd1);
	close(*fd2);
}
int
	main(int ac, char **av)
{
	int	fd1;
	int	fd2;

	if (ac != 5)
		return (0);
	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[4], O_RDONLY);
	printf("fd1 = %d\nfd2 = %d\n", fd1, fd2);
	if (fd2 == -1)
	{
		fd2 = open(av[4], O_CREAT | O_WRONLY | O_TRUNC, 00644);
		if (fd2 == -1)
		{
			printf("fd2 %d\n", fd2);
			ft_close_fdz(&fd1, &fd2);
			return (0);
		}
	}
	printf("nice\n");
	ft_close_fdz(&fd1, &fd2);
	return (0);
}
