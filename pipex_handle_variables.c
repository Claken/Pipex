/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_handle_variables.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 18:11:35 by sachouam          #+#    #+#             */
/*   Updated: 2021/10/02 18:52:52 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char
	**ft_empty_string_for_command(void)
{
	char	**tab;

	tab = malloc(sizeof(char *) * 2);
	if (!tab)
		return (NULL);
	tab[0] = ft_strdup("");
	if (!tab[0])
		return (NULL);
	tab[1] = NULL;
	return (tab);
}

static int
	ft_empty_command_s(char **av, t_prcs *process1, t_prcs *process2)
{
	if (!av[2][0])
	{
		process1->cmd = ft_empty_string_for_command();
		if (!process1->cmd)
		{
			ft_free_all_tabs(process1, process2);
			return (0);
		}
	}
	if (!av[3][0])
	{
		process2->cmd = ft_empty_string_for_command();
		if (!process2->cmd)
		{
			ft_free_all_tabs(process1, process2);
			return (0);
		}
	}
	return (1);
}

static int
	ft_if_path_exist(char **av, char **envp,
		t_prcs *process1, t_prcs *process2)
{
	char	**path;

	path = ft_tab_of_paths(envp);
	if (!path)
		return (0);
	if (!process1->cmd)
		process1->cmd = ft_handling_command(av[2], path);
	if (!process2->cmd)
		process2->cmd = ft_handling_command(av[3], path);
	ft_free_tab(path);
	if (!process1->cmd || !process2->cmd)
	{
		ft_free_all_tabs(process1, process2);
		return (0);
	}
	return (1);
}

static int
	ft_if_path_do_not_exist(char **av, t_prcs *process1, t_prcs *process2)
{
	if (!process1->cmd)
		process1->cmd = ft_handling_command_2(av[2]);
	if (!process2->cmd)
		process2->cmd = ft_handling_command_2(av[3]);
	if (!process1->cmd || !process2->cmd)
	{
		ft_free_all_tabs(process1, process2);
		return (0);
	}
	return (1);
}

int
	ft_set_variables(char **av, char **envp,
		t_prcs *process1, t_prcs *process2)
{
	if (!ft_set_struc(process1, process2, av))
		return (0);
	if (!av[2][0] || !av[3][0])
	{
		if (!ft_empty_command_s(av, process1, process2))
			return (0);
	}
	if (ft_check_if_path_exist(envp))
	{
		if (!ft_if_path_exist(av, envp, process1, process2))
			return (0);
	}
	else
	{
		if (!ft_if_path_do_not_exist(av, process1, process2))
			return (0);
	}
	return (1);
}
