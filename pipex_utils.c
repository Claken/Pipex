/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 00:39:51 by sachouam          #+#    #+#             */
/*   Updated: 2021/09/10 01:46:51 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void
	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
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
