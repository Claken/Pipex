/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_other_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 15:33:50 by sachouam          #+#    #+#             */
/*   Updated: 2021/09/21 15:33:55 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void
	ft_free_tab(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		free(tab[i]);
	}
	free(tab);
}

char
	*ft_strjoin_three(char const *s1, char const *s2, char const *s3)
{
	char	*firstjoin;
	char	*secondjoin;

	firstjoin = ft_strjoin(s1, s2);
	if (!firstjoin)
		return (NULL);
	secondjoin = ft_strjoin(firstjoin, s3);
	if (!secondjoin)
		return (NULL);
	free(firstjoin);
	return (secondjoin);
}

int
	ft_set_struc(t_prcs *process1, t_prcs *process2, char **av)
{
	process1->fd = 0;
	process1->id = 0;
	process1->cmd = NULL;
	process1->file = ft_strdup(av[1]);
	if (!process1->file)
		return (0);
	process2->fd = 0;
	process2->id = 0;
	process2->cmd = NULL;
	process2->file = ft_strdup(av[4]);
	if (!process2->file)
		return (0);
	return (1);
}

void
	ft_free_all_tabs(t_prcs *process1, t_prcs *process2)
{
	if (process1->cmd)
		ft_free_tab(process1->cmd);
	if (process2->cmd)
		ft_free_tab(process2->cmd);
	if (process1->file)
		free(process1->file);
	if (process2->file)
		free(process2->file);
}

int
	ft_check_if_path_exist(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	if (envp[i] == '\0')
		return (0);
	return (1);
}
