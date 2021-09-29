/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors_handling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 17:04:45 by sachouam          #+#    #+#             */
/*   Updated: 2021/09/29 17:15:14 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void
	ft_print_error_message(char *sentence, char *var)
{
	ft_putstr_fd("pipex: ", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(sentence, 2);
}

void
	ft_errors_handling(t_prcs *process, int num)
{
	if (!num && access(process->file, F_OK) == -1)
	{
		ft_print_error_message("No such file or directory", process->file);
	}
	else if (num && access(process->file, W_OK) == -1)
	{
		if (ft_strncmp(process->file, "\0", 1) == 0)
			ft_print_error_message("No such file or directory", process->file);
		else
			ft_print_error_message("Permission denied", process->file);
	}
	else if (!ft_strchr(process->cmd[0], '/'))
	{
		ft_print_error_message("Command not found", process->cmd[0]);
	}
	else if (ft_strchr(process->cmd[0], '/'))
	{
		if (access(process->cmd[0], F_OK) == -1)
			ft_print_error_message("No such file or directory",
				process->cmd[0]);
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

int
	ft_free_all_and_go(t_prcs *prc1, t_prcs *prc2)
{
	ft_free_all_tabs(prc1, prc2);
	return (0);
}
