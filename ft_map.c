/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:09:11 by tel-bouh          #+#    #+#             */
/*   Updated: 2025/08/27 19:57:23 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_zone	*ft_map(size_t aligned_size)
{
	t_zone	*zone;

	zone = mmap(NULL, aligned_size, PROT_READ
			| PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (zone == MAP_FAILED)
	{
		perror("mmap failed: ");
		return (NULL);
	}
	return (zone);
}

void	*ft_return_ptr(t_block *block)
{
	void	*ptr;

	ptr = (void *)((char *) block + sizeof(t_block));
	return (ptr);
}
