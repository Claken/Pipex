/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:04:45 by sachouam          #+#    #+#             */
/*   Updated: 2021/09/21 13:00:05 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void
	ft_errors_handling(char **envp, t_prcs *process)
{
	int	fd;

	fd = access(process->file, F_OK);
	if (fd == -1)
	{
		ft_putstr_fd("pipex: no such file or directory: ", 1);
		ft_putendl_fd(process->file, 1);
	}
	else if (!ft_strchr(process->cmd[0], '/'))
	{
		ft_putstr_fd("pipex: command not found: ", 1);
		ft_putendl_fd(process->cmd[0], 1);
	}
	else if (ft_strchr(process->cmd[0], '/'))
	{
		fd = access(process->cmd[0], F_OK);
		if (fd == -1)
		{
			ft_putstr_fd("pipex: no such file or directory: ", 1);
			ft_putendl_fd(process->cmd[0], 1);
		}
	}
	else
		perror("pipex");
}
