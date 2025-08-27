/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:18:13 by tel-bouh          #+#    #+#             */
/*   Updated: 2025/08/27 19:35:18 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (ft_putstr("(null)"));
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_puthex(unsigned int nbr, int flag)
{
	char	*base;
	char	tab[19];
	int		index;
	int		nb;

	base = "0123456789abcdef";
	nb = 0;
	index = 0;
	if (nbr == 0)
		return (ft_putchar('0'));
	while (nbr)
	{
		tab[index] = base[nbr % 16];
		if (tab[index] >= 'a')
			tab[index] -= flag;
		index++;
		nbr = nbr / 16;
	}
	nb = nb + index;
	while (index)
		write(1, &tab[--index], 1);
	return (nb);
}

int	ft_putint(int nbr)
{
	char	tab[10];
	int		i;
	int		nb;

	nb = 0;
	i = 0;
	if (nbr <= 0)
	{
		if (nbr == 0)
			return (ft_putstr("0"));
		else if (nbr == -2147483648)
			return (ft_putstr("-2147483648"));
		else
			nb = nb + ft_putstr("-");
		nbr = nbr * -1;
	}
	while (nbr)
	{
		tab[i++] = (nbr % 10) + 48;
		nbr /= 10;
	}
	nb = nb + i;
	while (i)
		write(1, &tab[--i], 1);
	return (nb);
}

int	ft_put_unsignedint(unsigned int nbr)
{
	char	tab[10];
	int		i;
	int		nb;

	nb = 0;
	i = 0;
	if (nbr == 0)
		return (ft_putchar('0'));
	while (nbr)
	{
		tab[i++] = (nbr % 10) + 48;
		nbr /= 10;
	}
	nb = i;
	while (i)
		write(1, &tab[--i], 1);
	return (nb);
}
