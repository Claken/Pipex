/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 17:36:48 by sachouam          #+#    #+#             */
/*   Updated: 2021/07/29 03:16:10 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int
	ft_char_in_charset(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char
	*ft_copy_case_tab(char *str, char *charset)
{
	int		i;
	char	*tab;

	i = 0;
	while (!(ft_char_in_charset(str[i], charset)) && str[i])
		i++;
	tab = malloc(sizeof(char) * (i + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (!(ft_char_in_charset(str[i], charset)) && str[i])
	{
		tab[i] = str[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

int
	ft_count_words(char *str, char *charset)
{
	int	nb;
	int	i;

	i = 0;
	nb = 0;
	while (str[i])
	{
		if (!(ft_char_in_charset(str[i], charset)))
		{
			nb++;
			while (!(ft_char_in_charset(str[i], charset)) && str[i])
				i++;
		}
		else
			i++;
	}
	return (nb);
}

static int
	ft_set_variables(int *i, int *j, char *str, char *charset)
{
	int	tmp;

	*i = 0;
	*j = 0;
	tmp = ft_count_words(str, charset);
	return (tmp);
}

char
	**ft_split(char *str, char *charset)
{
	char	**tab;
	int		nb;
	int		i;
	int		j;

	nb = ft_set_variables(&i, &j, str, charset);
	tab = malloc(sizeof(char *) * (nb + 1));
	if (!tab)
		return (NULL);
	while (str[i])
	{
		if (!(ft_char_in_charset(str[i], charset)))
		{
			tab[j] = ft_copy_case_tab(str + i, charset);
			if (tab[j] == NULL)
				return (NULL);
			while (!(ft_char_in_charset(str[i], charset)) && str[i])
				i++;
			j++;
		}
		else
			i++;
	}
	tab[j] = 0;
	return (tab);
}
