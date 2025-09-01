/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_allocate_large_zone.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:07:03 by tel-bouh          #+#    #+#             */
/*   Updated: 2025/09/01 19:32:10 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

/*
 * The actual RAM memory available is around
 * 64 GB but the kernel tell 
 * a process you can have more arount 128TIB 
 * in 64 architecture, those called soft and hard limit
 * soft limit is how mutch a process can have
 * and hard limit is how soft limit could rise
 * how that can happen, this related to concept
 * of paging in RAM only needed (active) pages been in RAM 
 * and non-active pages moved to swap or deleted ,
 * that how we achieve move that phusucal RAM
 */

static int	ft_add_overflow_size(size_t a, size_t b, size_t *out)
{
	return (__builtin_add_overflow(a, b, out));
}

int	ft_print_error(char *error)
{
	int	i;

	i = 0;
	while (error[i])
		i++;
	write(2, error, i);
	return (1);
}

int	ft_check_error(size_t nbr_of_bytes)
{
	t_rlimit	lim;
	size_t		total_size;
	size_t		aligned_size;
	size_t		total;
	size_t		max_va_conservative;

	max_va_conservative = (size_t)1ULL << 47;
	total_size = sizeof(t_zone) + sizeof(t_block);
	if (ft_add_overflow_size(total_size, nbr_of_bytes, &total))
		return (ft_print_error("error\n"));
	aligned_size = align16(total);
	if (aligned_size < total)
		return (ft_print_error("error\n"));
	getrlimit(RLIMIT_AS, &lim);
	if (aligned_size > lim.rlim_cur)
		return (ft_print_error("error\n"));
	if (getrlimit(RLIMIT_AS, &lim) == 0 && lim.rlim_cur != RLIM_INFINITY)
	{
		if ((unsigned long long)aligned_size > (unsigned long long)lim.rlim_cur)
			return (ft_print_error("error\n"));
	}
	else if (aligned_size > max_va_conservative)
		return (ft_print_error("error\n"));
	return (0);
}

void	ft_push_large_zone(t_zone *zone)
{
	t_zone	*temp_zone;

	temp_zone = g_zone_var.large;
	while (temp_zone->next != NULL)
		temp_zone = temp_zone->next;
	temp_zone->next = zone;
}

void	*ft_allocate_large_zone(size_t nbr_of_bytes)
{
	t_zone	*zone;
	t_block	*block;
	size_t	aligned_size;

	if (ft_check_error(nbr_of_bytes))
		return (NULL);
	aligned_size = align16((sizeof(t_zone) + sizeof(t_block) + nbr_of_bytes));
	ft_printf("aligned large %l %l %l\n", aligned_size , sizeof(t_zone), sizeof(t_block));
	zone = ft_map(aligned_size);
	if (zone == NULL)
		return (NULL);
	zone->zone_size = aligned_size;
	zone->next = NULL;
	zone->blocks = (t_block *)((char *)zone + sizeof(t_zone));
	block = zone->blocks;
	block->size = aligned_size - sizeof(t_zone) - sizeof(t_block);
	block->free = 0;
	block->next = NULL;
	block->zone_id = 2;
	if (g_zone_var.large == NULL)
		g_zone_var.large = zone;
	else
		ft_push_large_zone(zone);
	return (ft_return_ptr(block));
}
