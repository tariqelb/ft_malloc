/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocate_new_page.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:07:40 by tel-bouh          #+#    #+#             */
/*   Updated: 2025/09/04 11:58:33 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_malloc.h"

void	ft_push_zone(int zone_index, t_zone *zone)
{
	t_zone	*temp_zone;

	if (zone_index == 0)
		temp_zone = g_zone_var.tiny;
	else
		temp_zone = g_zone_var.small;
	if (temp_zone == NULL && zone_index == 0)
		g_zone_var.tiny = zone;
	else if (temp_zone == NULL && zone_index == 1)
		g_zone_var.small = zone;
	else
	{
		if (zone_index == 0)
			temp_zone = g_zone_var.tiny;
		else
			temp_zone = g_zone_var.small;
		while (temp_zone && temp_zone->next != NULL)
			temp_zone = temp_zone->next;
		temp_zone->next = zone;
	}
}

t_zone	*ft_allocate_new_page(int zone_index)
{
	size_t	page_size;
	t_zone	*zone;

	if (zone_index == 0)
		page_size = 16 * g_zone_var.mapping_size;
	else
		page_size = 1024 * g_zone_var.mapping_size;
	zone = mmap(NULL, page_size, PROT_READ
			| PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (zone == MAP_FAILED)
	{
		write(2, "mmap failed\n", 12);
		return (NULL);
	}
	zone->zone_size = page_size;
	zone->next = NULL;
	zone->blocks = (t_block *)((char *)zone + sizeof(t_zone));
	zone->blocks->size = page_size - sizeof(t_zone) - sizeof(t_block);
	zone->blocks->free = 1;
	zone->blocks->magic_number = BLOCK_MAGIC;
	zone->blocks->next = NULL;
	zone->largest_free_block_size = page_size
		- sizeof(t_zone) - sizeof(t_block);
	ft_push_zone(zone_index, zone);
	return (zone);
}
