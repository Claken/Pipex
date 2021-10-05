/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_functions_for_commands.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:38:52 by sachouam          #+#    #+#             */
/*   Updated: 2021/10/05 14:43:15 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char
	**ft_tab_of_paths(char **envp)
{
	int		i;
	char	**tab;

	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	tab = ft_split(envp[i] + 5, ":");
	if (tab == NULL)
		return (NULL);
	return (tab);
}

static char
	*ft_find_cmd(char **path, char *cmd)
{
	int		i;
	char	*cmdpath;
	int		fd;

	i = -1;
	if (!ft_strchr(cmd, '/'))
	{
		while (path[++i])
		{
			cmdpath = ft_strjoin_three(path[i], "/", cmd);
			if (!cmdpath)
				return (NULL);
			fd = access(cmdpath, F_OK);
			if (fd == 0)
				return (cmdpath);
			free(cmdpath);
		}
	}
	cmdpath = ft_strdup(cmd);
	if (!cmdpath)
		return (NULL);
	return (cmdpath);
}

static char
	**ft_create_pathandflag(char *s1, char *s2)
{
	char	**tab;
	int		lens1;
	int		lens2;

	tab = malloc(sizeof(char *) * 3);
	if (!tab)
		return (NULL);
	lens1 = ft_strlen(s1);
	tab[0] = malloc(sizeof(char) * (lens1 + 1));
	if (!tab[0])
		return (NULL);
	ft_strlcpy(tab[0], s1, lens1 + 1);
	if (s2)
	{
		lens2 = ft_strlen(s2);
		tab[1] = malloc(sizeof(char) * (lens2 + 1));
		if (!tab[1])
			return (NULL);
		ft_strlcpy(tab[1], s2, lens2 + 1);
	}
	else
		tab[1] = NULL;
	tab[2] = NULL;
	return (tab);
}

char
	**ft_handling_command(char *arg, char **path)
{
	char	**cmdtab;
	char	*cmdpath;
	char	**pathandflag;

	cmdtab = ft_split(arg, " ");
	if (!cmdtab)
		return (NULL);
	cmdpath = ft_find_cmd(path, cmdtab[0]);
	if (!cmdpath)
	{
		ft_free_tab(cmdtab);
		return (NULL);
	}
	pathandflag = ft_create_pathandflag(cmdpath, cmdtab[1]);
	free(cmdpath);
	ft_free_tab(cmdtab);
	if (!pathandflag)
		return (NULL);
	return (pathandflag);
}

char
	**ft_handling_command_2(char *arg)
{
	char	**cmdtab;
	char	**pathandflag;

	cmdtab = ft_split(arg, " ");
	if (!cmdtab)
		return (NULL);
	pathandflag = ft_create_pathandflag(cmdtab[0], cmdtab[1]);
	ft_free_tab(cmdtab);
	if (!pathandflag)
		return (NULL);
	return (pathandflag);
}
