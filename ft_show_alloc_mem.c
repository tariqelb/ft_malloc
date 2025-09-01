/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_alloc_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:10:12 by tel-bouh          #+#    #+#             */
/*   Updated: 2025/09/01 17:58:58 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	ft_display_block(int j, t_block *block)
{
	void	*ptr;

	ptr = (void *)((char *) block + (sizeof (t_block)));
	ft_printf("block [%d] : block address [%p]\n", j + 1, block);
	ft_printf("block [%d] : block next address [%p]\n", j + 1, block->next);
	ft_printf("block [%d] : ptr addr [%p]\n", j + 1, ptr);
	ft_printf("block [%d] : block size [%l] \n", j + 1, block->size);
	ft_printf("block [%d] : block is free [%d] \n", j + 1, block->free);
	ft_printf("block [%d] : block zone id [%d] \n", j + 1, block->zone_id);
}

void	ft_display_zone_header(int i, t_zone *zone, char *zone_name)
{
	ft_printf("%s [%d] : zone address [%p]\n", zone_name, i + 1, zone);
	ft_printf("%s [%d] : zone next address [%p]\n", zone_name, i + 1, zone->next);
	ft_printf("%s [%d] : zone lagest free block [%l]\n", zone_name,
		i + 1, zone->largest_free_block_size);
	ft_printf("-----------Blocks start----------------------\n");
}

void	ft_display_zone(int i, t_zone *zone, char *zone_name)
{
	t_block	*block;
	int	j;

	i = 0;
	ft_printf("---------------------------------------------\n");
	ft_printf("----------START OF %s ZONE-----------------\n", zone_name);
	ft_printf("Display %s zone :\n", zone_name);
	while (zone)
	{
		ft_display_zone_header(i, zone, zone_name);
		block = zone->blocks;
		j = 0;
		while (block)
		{
			ft_display_block(j, block);
			block = block->next;
			j++;
		}
		ft_printf("-----------Blocks end ----------------------\n");
		zone = zone->next;
		i++;
	}
	ft_printf("---------------------------------------------\n");
	ft_printf("-------------END OF TINY ZONE----------------\n");
}

void	show_alloc_mem(void)
{
	t_zone	*tiny;
	t_zone	*small;
	t_zone	*large;
	int	i;

	i = 0;
	tiny = g_zone_var.tiny;
	small = g_zone_var.small;
	large = g_zone_var.large;
	if (tiny)
		ft_display_zone(i, tiny, "TINY");
	else
		ft_printf("-------------------Tiny zone is empty-------------\n");
	if (small)
		ft_display_zone(i, small, "SMALL");
	else
		printf("-----------------Small zone is empty---------------\n");
	if (large)
		ft_display_zone(i, large, "LARGE");
	else
		printf("-----------------Large zone is empty---------------\n");
}
