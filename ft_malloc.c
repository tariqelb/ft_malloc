/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:08:35 by tel-bouh          #+#    #+#             */
/*   Updated: 2025/09/01 20:04:15 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_malloc.h"

t_g_zone_hold	g_zone_var = {NULL, NULL, NULL, 0};

void	*malloc(size_t nbr_of_bytes)
{
	int	is_full;
	int	zone;
	void	*ptr;

	ptr = NULL;
	g_zone_var.mapping_size = getpagesize();
	zone = ft_choose_zone(nbr_of_bytes);
	if (zone == -1)
		return (NULL);
	else if (zone == 0 || zone == 1)
	{
		is_full = ft_check_if_zone_is_full(zone, nbr_of_bytes);
		if (is_full == 0)
			ptr = ft_find_the_best_free_block(zone, nbr_of_bytes);
		else
		{
			if (ft_allocate_new_page(zone))
				ptr = ft_find_the_best_free_block(zone, nbr_of_bytes);
		}
		return (ptr);
	}
	else
		return (ft_allocate_large_zone(nbr_of_bytes));
	return (ptr);
}
