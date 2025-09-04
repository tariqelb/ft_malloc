/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:07:54 by tel-bouh          #+#    #+#             */
/*   Updated: 2025/09/04 11:56:56 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
 * ft_merge_free_block
 * this fuction merge two continuous free block on zone tiny and small
 * and free the zone if the block on large zone
 */

void	ft_free_large_zone(void)
{
	t_zone	*prev;
	t_zone	*curr;

	prev = NULL;
	curr = g_zone_var.large;
	while (curr)
	{
		if (curr->blocks->free)
		{
			if (prev)
				prev->next = curr->next;
			else
				g_zone_var.large = curr->next;
			munmap(curr, curr->zone_size);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

t_zone	*ft_get_zone(int zone_id)
{
	t_zone	*temp_zone;

	temp_zone = g_zone_var.tiny;
	if (zone_id == 1)
		temp_zone = g_zone_var.small;
	return (temp_zone);
}

void	ft_merge_free_blocks(t_block *block)
{
	t_zone	*temp_zone;
	t_block	*curr;

	if (block->zone_id == 0 || block->zone_id == 1)
	{
		temp_zone = ft_get_zone(block->zone_id);
		while (temp_zone)
		{
			curr = temp_zone->blocks;
			while (curr && curr->next)
			{
				if (curr->free && curr->next->free)
				{
					curr->size += sizeof(t_block) + curr->next->size;
					curr->next = curr->next->next;
				}
				else
					curr = curr->next;
			}
			ft_update_largest_free_block_size(temp_zone);
			temp_zone = temp_zone->next;
		}
	}
	else if (block->zone_id == 2)
		ft_free_large_zone();
}

void	free(void *ptr)
{
	t_block		*block;
	uintptr_t	addr_ptr;

	addr_ptr = (uintptr_t) ptr;
	if (addr_ptr % 16)
	{
		write(2, "Invalid pointer\n", 16);
		return ;
	}
	block = (t_block *)((char *)ptr - sizeof(t_block));
	if (block->magic_number != BLOCK_MAGIC)
	{
		write(2, "Invalid pointer\n", 16);
		return ;
	}
	block->free = 1;
	ft_merge_free_blocks(block);
	return ;
}
