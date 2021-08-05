/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sachouam <sachouam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 13:46:15 by sachouam          #+#    #+#             */
/*   Updated: 2021/07/29 02:05:43 by sachouam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char
	*ft_revstr(char *str)
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	j = 0;
	while (str[j] != '\0')
		j++;
	j--;
	if (*str == '-')
		i++;
	while (i < j)
	{
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
	return (str);
}

void
	ft_write_in_nbr(long n, char *nbr)
{
	int		i;
	long	nb;

	i = 0;
	nb = n;
	if (nb < 0)
	{
		nbr[i++] = '-';
		nb = nb * (-1);
	}
	else if (nb == 0)
		nbr[i++] = nb + '0';
	if (nb > 0)
	{
		while (nb != 0)
		{
			nbr[i++] = nb % 10 + '0';
			nb = nb / 10;
		}
	}
	nbr[i] = '\0';
}

char
	*ft_itoa(int n)
{
	char	*nbr;
	long	nb;

	nbr = malloc(sizeof(char) * 12);
	if (!nbr)
		return (NULL);
	nb = n;
	ft_write_in_nbr(nb, nbr);
	nbr = ft_revstr(nbr);
	return (nbr);
}
