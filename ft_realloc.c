/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:09:48 by tel-bouh          #+#    #+#             */
/*   Updated: 2025/09/04 12:10:32 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

//this function use the same block because its 
//size enough and split it if the remain bytes
//can create a new block
void	*ft_use_the_block(t_block *block, void *ptr, size_t aligned_size)
{
	size_t	excess;
	t_block	*new_block;

	excess = block->size - aligned_size;
	if (excess >= sizeof(t_block) + 16)
	{
		new_block = (t_block *)((char *)block + sizeof(t_block) + aligned_size);
		new_block->size = excess - sizeof(t_block);
		new_block->free = 1;
		new_block->magic_number = BLOCK_MAGIC;
		new_block->next = block->next;
		new_block->zone_id = block->zone_id;
		block->size = aligned_size;
		block->next = new_block;
	}
	return (ptr);
}

//normmaly the split should be if remain bytes can
//create the minimum block which is sizeof(t_block)						     
//+ 16 , not 1 bytes , its ok
//case one split next block and take only requered
//bytes and case two use the whole block
void	*ft_use_next_free_block(t_block *block, void *ptr, size_t aligned_size)
{
	size_t	total;
	t_block	*new_block;

	total = block->size + sizeof(t_block) + block->next->size;
	if (aligned_size <= total)
	{
		if ((total - aligned_size) >= sizeof(t_block) + 1)
		{
			new_block = (t_block *)((char *)block
					+ sizeof(t_block) + aligned_size);
			new_block->size = total - aligned_size - sizeof(t_block);
			new_block->free = 1;
			new_block->magic_number = BLOCK_MAGIC;
			new_block->zone_id = block->zone_id;
			new_block->next = block->next->next;
			block->size = aligned_size;
			block->next = new_block;
		}
		else
		{
			block->size = total;
			block->next = block->next->next;
		}
	}
	return (ptr);
}

void	*ft_new_block(size_t size, size_t aligned_size,
		t_block *block, void *ptr)
{
	void	*new_ptr;
	size_t	to_copy;

	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	if (block->size < aligned_size)
		to_copy = block->size;
	else
		to_copy = aligned_size;
	memcpy(new_ptr, ptr, to_copy);
	free(ptr);
	return (new_ptr);
}

void	*realloc(void *ptr, size_t size)
{
	t_block	*block;
	size_t	aligned_size;
	void	*new_ptr;
	int		zone;
	int		temp_zone;

	block = (t_block *)((char *) ptr - sizeof(t_block));
	if (block->magic_number != BLOCK_MAGIC)
		return (NULL);
	aligned_size = align16(size);
	zone = ft_choose_zone(size);
	temp_zone = zone;
	new_ptr = ft_first_check(ptr, size, &zone, block);
	if (zone != 4)
		return (new_ptr);
	zone = temp_zone;
	new_ptr = ft_second_check(ptr, size, &zone, block);
	if (zone != 4)
		return (new_ptr);
	zone = temp_zone;
	if (block->size >= aligned_size)
		return (ft_use_the_block(block, ptr, aligned_size));
	if (block->next && block->next->free == 1)
		return (ft_use_next_free_block(block, ptr, aligned_size));
	return (ft_new_block(size, aligned_size, block, ptr));
}
