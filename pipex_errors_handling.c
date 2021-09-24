/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:04:45 by sachouam          #+#    #+#             */
/*   Updated: 2021/09/24 02:14:14 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void
	ft_errors_handling(t_prcs *process)
{
	int	fd;

	fd = access(process->file, F_OK);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putendl_fd(process->file, 2);
	}
	else if (!ft_strchr(process->cmd[0], '/'))
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(process->cmd[0], 2);
	}
	else if (ft_strchr(process->cmd[0], '/'))
	{
		fd = access(process->cmd[0], F_OK);
		if (fd == -1)
		{
			ft_putstr_fd("pipex: no such file or directory: ", 2);
			ft_putendl_fd(process->cmd[0], 2);
		}
	}
	else
		perror("pipex");
}

void
	ft_free_if_execve_fail(t_prcs *process, int pi[])
{
	close(pi[0]);
	close(pi[1]);
	if (process->cmd)
		ft_free_tab(process->cmd);
	if (process->file)
		free(process->file);
}

void
	ft_fief_and_exit(t_prcs *process, int pi[])
{
	ft_free_if_execve_fail(process, pi);
	exit(0);
}
