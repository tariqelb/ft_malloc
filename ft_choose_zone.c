/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_choose_zone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:40:57 by tel-bouh          #+#    #+#             */
/*   Updated: 2025/09/04 12:08:44 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int	ft_choose_zone(size_t nbr_of_bytes)
{
	int	zone;

	zone = 0;
	if (nbr_of_bytes <= TINY)
		return (0);
	else if (nbr_of_bytes > TINY && nbr_of_bytes <= SMALL)
		return (1);
	else if (nbr_of_bytes >= 1024)
		return (2);
	return (zone);
}

int	ft_check_if_zone_is_full(int zone, size_t nbr_of_bytes)
{
	int		is_full;
	int		size;
	t_zone	*temp_zone;

	size = nbr_of_bytes + sizeof(t_block);
	is_full = 1;
	if (zone == 0)
		temp_zone = g_zone_var.tiny;
	else
		temp_zone = g_zone_var.small;
	while (temp_zone != NULL)
	{
		if (temp_zone->largest_free_block_size >= (size_t) size)
			return (0);
		temp_zone = temp_zone->next;
	}
	return (is_full);
}
