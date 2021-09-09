/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/06 01:05:40 by sachouam          #+#    #+#             */
/*   Updated: 2021/09/10 00:45:14 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "libft/libft.h"

void	ft_free_tab(char **tab);
char	*ft_strjoin_three(char const *s1,
			char const *s2, char const *s3);
char	**ft_tab_of_paths(char **envp);
char	*ft_find_cmd(char **path, char *cmd);
char	**ft_handling_command(char *arg, char **path);

#endif
