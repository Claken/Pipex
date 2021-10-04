/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:04:45 by sachouam          #+#    #+#             */
/*   Updated: 2021/10/04 17:44:27 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void
	ft_print_error_message(t_prcs *process, int file, char *phrase)
{
	ft_putstr_fd("pipex: ", 2);
	if (file)
		ft_putstr_fd(process->file, 2);
	else
		ft_putstr_fd(process->cmd[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(phrase, 2);
}

void
	ft_errors_handling(t_prcs *process, char **envp)
{
	if (process->fd == -1)
	{
		ft_print_error_message(process, 1, strerror(errno));
		process->statut = 1;
	}
	else
	{
		if (!ft_strchr(process->cmd[0], '/') && ft_check_if_path_exist(envp))
		{
			ft_print_error_message(process, 0, "Command not found");
		}
		else
		{
			if (access(process->cmd[0], F_OK) == -1)
				ft_print_error_message(process, 0, "No such file or directory");
		}
		process->statut = 127;
	}
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
	ft_fief_and_exit(t_prcs *process, t_prcs *retreive)
{
	ft_free_if_execve_fail(process);
	exit(retreive->statut);
}

int
	ft_free_all_and_go(t_prcs *prc1, t_prcs *prc2)
{
	ft_free_all_tabs(prc1, prc2);
	return (1);
}
