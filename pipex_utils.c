/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 00:39:51 by sachouam          #+#    #+#             */
/*   Updated: 2021/09/20 13:18:12 by sachouam         ###   ########.fr       */
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

void
	ft_set_struc(t_prcs *process1, t_prcs *process2)
{
	process1->fd = 0;
	process1->id = 0;
	process1->cmd = NULL;
	process2->fd = 0;
	process2->id = 0;
	process2->cmd = NULL;
}

void
	ft_free_all_tabs(t_prcs *process1, t_prcs *process2)
{
	if (process1->cmd)
		ft_free_tab(process1->cmd);
	if (process2->cmd)
		ft_free_tab(process2->cmd);
}
