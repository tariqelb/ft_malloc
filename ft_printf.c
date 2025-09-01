/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 22:30:19 by tel-bouh          #+#    #+#             */
/*   Updated: 2025/09/01 17:59:50 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int ft_putsize_t(size_t nbr)
{
    char tab[32];       // enough to hold 64-bit number
    int  i = 0;
    int  nb = 0;

    if (nbr == 0)
        return ft_putstr("0");

    while (nbr)
    {
        tab[i++] = (nbr % 10) + '0';
        nbr /= 10;
    }

    nb = i;
    while (i)
        write(1, &tab[--i], 1);

    return nb;
}

static int	ft_puthex_add(unsigned long long int nbr)
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
		index++;
		nbr = nbr / 16;
	}
	nb = nb + index;
	while (index)
		write(1, &tab[--index], 1);
	return (nb);
}

static int	ft_specifier(char c)
{
	int		i;
	char	*specifiers;

	specifiers = "cspdiuxXl";
	i = 0;
	while (specifiers[i])
	{
		if (specifiers[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_switch_case(va_list arg_list, char c, int nb)
{
	if (c == 'c')
		nb = nb + ft_putchar((va_arg(arg_list, int)));
	else if (c == 's')
		nb = nb + ft_putstr(va_arg(arg_list, char *));
	else if (c == 'p')
	{
		nb = nb + ft_putstr("0x");
		nb = nb + ft_puthex_add(va_arg(arg_list, unsigned long long int));
	}
	else if (c == 'd')
		nb = nb + ft_putint(va_arg(arg_list, int));
	else if (c == 'l')
		nb = nb + ft_putsize_t(va_arg(arg_list, int));
	else if (c == 'i')
		nb = nb + ft_putint(va_arg(arg_list, int));
	else if (c == 'u')
		nb = nb + ft_put_unsignedint(va_arg(arg_list, unsigned int));
	else if (c == 'x')
		nb = nb + ft_puthex(va_arg(arg_list, unsigned int), 0);
	else if (c == 'X')
		nb = nb + ft_puthex(va_arg(arg_list, unsigned int), 32);
	else if (c == '%')
		nb = nb + ft_putchar('%');
	return (nb);
}

int	ft_printf(const char *str, ...)
{
	int		index;
	int		nb;
	va_list	args;

	va_start(args, str);
	nb = 0;
	index = 0;
	while (str[index])
	{
		if (str[index] == '%')
		{
			index++;
			if (ft_specifier(str[index]) == 1)
				nb = ft_switch_case(args, str[index], nb);
			else
				nb = nb + ft_putchar(str[index]);
			index++;
		}
		else
			nb = nb + ft_putchar(str[index++]);
	}
	va_end(args);
	return (nb);
}
