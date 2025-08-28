/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocate_block.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 23:43:24 by tel-bouh          #+#    #+#             */
/*   Updated: 2025/08/28 18:40:37 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*ft_find_the_best_free_block(int zone, size_t nbr_of_bytes)
{
	t_zone	*temp_zone;
	t_block	*best_free_block;
	size_t	aligned_size;

	aligned_size = align16(nbr_of_bytes);
	if (zone == 0)
		temp_zone = g_zone_var.tiny;
	else
		temp_zone = g_zone_var.small;
	best_free_block = NULL;
	while (temp_zone != NULL)
	{
		if (temp_zone->largest_free_block_size >= aligned_size)
		{
			best_free_block
				= ft_resize_largest_free_block(nbr_of_bytes, temp_zone, zone);
			return (best_free_block);
		}
		temp_zone = temp_zone->next;
	}
	return (best_free_block);
}

void	*ft_return_whole_block(t_block *temp_block, int zone, t_zone *page_ptr)
{
	temp_block->free = 0;
	temp_block->zone_id = zone;
	ft_update_largest_free_block_size(page_ptr);
	return ((void *)((char *)temp_block + sizeof(t_block)));
}

void	*ft_split_block(t_block *temp_block,
		size_t aligned_size, int zone, t_zone *page_ptr)
{
	t_block	*new_block;

	new_block = (t_block *)((char *)temp_block
			+ sizeof(t_block) + aligned_size);
	new_block->next = temp_block->next;
	new_block->size = temp_block->size - aligned_size - sizeof(t_block);
	new_block->free = 1;
	new_block->zone_id = zone;
	temp_block->next = new_block;
	temp_block->size = aligned_size;
	temp_block->free = 0;
	temp_block->zone_id = zone;
	ft_update_largest_free_block_size(page_ptr);
	return ((void *)((char *)temp_block + sizeof(t_block)));
}

void	*ft_resize_largest_free_block(size_t nbr_of_bytes,
		t_zone *page_ptr, int zone)
{
	t_block	*temp_block;
	size_t	largest_free_block;
	size_t	aligned_size;

	aligned_size = align16(nbr_of_bytes);
	largest_free_block = page_ptr->largest_free_block_size;
	temp_block = page_ptr->blocks;
	while (temp_block != NULL)
	{
		if (temp_block->free == 1 && temp_block->size == largest_free_block)
		{
			if (temp_block->size - aligned_size >= sizeof(t_block) + 1)
				return (ft_split_block(temp_block,
						aligned_size, zone, page_ptr));
			else if (temp_block->size >= aligned_size)
				return (ft_return_whole_block(temp_block, zone, page_ptr));
		}
		temp_block = temp_block->next;
	}
	return (NULL);
}

void	ft_update_largest_free_block_size(t_zone *page_ptr)
{
	size_t	new_size;
	t_block	*temp_block;

	temp_block = page_ptr->blocks;
	new_size = 0;
	while (temp_block != NULL)
	{
		if (temp_block->free)
		{
			if (temp_block->size > new_size)
				new_size = temp_block->size;
		}
		temp_block = temp_block->next;
	}
	page_ptr->largest_free_block_size = new_size;
}
