/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 17:33:40 by sachouam          #+#    #+#             */
/*   Updated: 2021/10/03 20:33:00 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int
	ft_how_to_use_the_function(void)
{
	ft_putendl_fd("usage: ./pipex file1 cmd1 cmd2 file2", 2);
	return (0);
}

static int
	ft_make_a_fork(t_prcs *process)
{
	process->id = fork();
	if (process->id < 0)
		return (0);
	return (1);
}

static void
	ft_dup2_and_execve(int num, int pi[], char **envp, t_prcs *process)
{
	int	numm;

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
	ft_errors_handling(process);
	ft_free_if_execve_fail(process);
}

static void
	ft_second_fork(t_prcs *process2, t_prcs *process1, char **envp, int pi[])
{
	pid_t	prowait;

	if (process2->id == 0)
	{
		process2->fd = open(process2->file,
				O_CREAT | O_WRONLY | O_TRUNC, 00664);
		ft_dup2_and_execve(1, pi, envp, process2);
		ft_fief_and_exit(process1);
	}
	else
	{
		close(pi[0]);
		close(pi[1]);
		prowait = 0;
		while (prowait != -1)
			prowait = wait(NULL);
	}
}

int
	main(int ac, char **av, char **envp)
{
	int		pi[2];
	t_prcs	process1;
	t_prcs	process2;

	if (ac != 5)
		return (ft_how_to_use_the_function());
	if (!ft_set_variables(av, envp, &process1, &process2)
		|| pipe(pi) == -1 || !ft_make_a_fork(&process1))
		return (ft_free_all_and_go(&process1, &process2));
	if (process1.id == 0)
	{
		process1.fd = open(process1.file, O_RDONLY);
		ft_dup2_and_execve(0, pi, envp, &process1);
		ft_fief_and_exit(&process2);
	}
	else
	{
		if (!ft_make_a_fork(&process2))
			return (ft_free_all_and_go(&process1, &process2));
		ft_second_fork(&process2, &process1, envp, pi);
	}
	ft_free_all_tabs(&process1, &process2);
	return (0);
}
