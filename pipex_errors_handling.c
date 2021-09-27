/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:04:45 by sachouam          #+#    #+#             */
/*   Updated: 2021/09/27 20:17:41 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void
	ft_if_num_is_one(t_prcs *process)
{
	if (ft_strncmp(process->file, "\0", 0) == 0)
		ft_putstr_fd("pipex: no such file or directory: ", 2);
	else
		ft_putstr_fd("pipex: permission denied: ", 2);
	ft_putendl_fd(process->file, 2);
}

void
	ft_errors_handling(t_prcs *process, int num)
{
	if (!num && access(process->file, F_OK) == -1)
	{
		ft_putstr_fd("pipex: no such file or directory: ", 2);
		ft_putendl_fd(process->file, 2);
	}
	else if (num && access(process->file, W_OK) == -1)
	{
		ft_if_num_is_one(process);
	}
	else if (!ft_strchr(process->cmd[0], '/'))
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(process->cmd[0], 2);
	}
	else if (ft_strchr(process->cmd[0], '/'))
	{
		if (access(process->cmd[0], F_OK) == -1)
		{
			ft_putstr_fd("pipex: no such file or directory: ", 2);
			ft_putendl_fd(process->cmd[0], 2);
		}
	}
	else
		perror("pipex");
}

void
	ft_free_if_execve_fail(t_prcs *process)
{
	if (process->cmd)
		ft_free_tab(process->cmd);
	if (process->file)
		free(process->file);
}

void
	ft_fief_and_exit(t_prcs *process)
{
	ft_free_if_execve_fail(process);
	exit(0);
}
