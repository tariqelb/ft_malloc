/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 19:15:56 by tel-bouh          #+#    #+#             */
/*   Updated: 2025/09/05 14:52:25 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*ft_first_check(void *ptr, size_t size, int *zone, t_block *block)
{
	size_t	aligned_size;

	if (ft_check_overflow(size))
	{
		*zone = 4;
		return (NULL);
	}
	aligned_size = align16(size);
	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	if (block->size >= aligned_size)
		return (ptr);
	*zone = 4;
	return (ptr);
}

void	*ft_second_check(void *ptr, size_t size, int *zone, t_block *block)
{
	void	*new_ptr;

	if (*zone == 2 || *zone != block->zone_id)
	{
		new_ptr = malloc(size);
		if (!new_ptr)
		{
			if (ptr)
				free(ptr);
			return (NULL);
		}
		memcpy(new_ptr, ptr, block->size);
		free(ptr);
		return (new_ptr);
	}
	*zone = 4;
	return (ptr);
}
