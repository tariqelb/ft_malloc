/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_alloc_mem.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:10:12 by tel-bouh          #+#    #+#             */
/*   Updated: 2025/08/27 19:39:20 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"


void	show_alloc_mem(void)
{
	t_zone	*tiny;
	t_zone	*small;
	t_zone	*large;
	t_block	*block;
	int	i;
	int	j;

	tiny = g_zone_var.tiny;
	small = g_zone_var.small;
	large = g_zone_var.large;
	i = 0;
	if (tiny)
	{
		ft_printf("---------------------------------------------\n");
		ft_printf("----------START OF TINY ZONE-----------------\n");
		ft_printf("Display tiny zone :\n");
		while (tiny)
		{
			ft_printf("Tiny [%d] : zone address [%p]\n", i + 1, tiny);
			ft_printf("Tiny [%d] : zone next address [%p]\n", i + 1 , tiny->next);
			ft_printf("Tiny [%d] : zone lagest free block [%ld]\n", i + 1, tiny->largest_free_block_size);
			ft_printf("-----------Blocks start----------------------\n");
			block = tiny->blocks;
			j = 0;
			while (block)
			{
				ft_printf("block [%d] : block address [%p]\n", j + 1, block);
				ft_printf("block [%d] : block next address [%p]\n", j + 1, block->next);
			ft_printf("block [%d] : ptr addr [%p]\n", j + 1, (void *)((char *) block + (sizeof (t_block))));
				ft_printf("block [%d] : block size [%ld] \n", j + 1, block->size);
				ft_printf("block [%d] : block is free [%d] \n", j + 1, block->free);
				ft_printf("block [%d] : block zone id [%d] \n", j + 1, block->zone_id);
				block = block->next;
				j++;
			}
			ft_printf("-----------Blocks end ----------------------\n");
			tiny = tiny->next;
			i++;
		}
		ft_printf("---------------------------------------------\n");
		ft_printf("-------------END OF TINY ZONE----------------\n");
	}
	else
		ft_printf("-------------------Tiny zone is empty-------------\n");


	/*i = 0;
	if (small)
	{
		printf("---------------------------------------------\n");
		printf("----------START OF SMALL ZONE----------------\n");
		printf("Display small zone :\n");
		while (small)
		{
			printf("Small [%d] : zone address [%p]\n", i + 1, small);
			printf("Small [%d] : zone next address [%p]\n", i + 1, small->next);
			printf("Small [%d] : zone lagest free block [%ld]\n", i + 1, small->largest_free_block_size);
			printf("-----------Blocks start----------------------\n");
			block = small->blocks;
			j = 0;
			while (block)
			{
				printf("block [%d] : block address [%p]\n", j + 1, block);
				printf("block [%d] : block next address [%p]\n", j + 1, block->next);
			printf("block [%d] : ptr addr [%p]\n", j + 1, (void *)((char *) block + (sizeof (t_block))));
				printf("block [%d] : block size [%ld] \n", j + 1, block->size);
				printf("block [%d] : block is free [%d] \n", j + 1, block->free);
				printf("block [%d] : block zone id [%d] \n", j + 1, block->zone_id);
				block = block->next;
				j++;
			}
			printf("-----------Blocks end ----------------------\n");
			small = small->next;
			i++;
		}
		printf("---------------------------------------------\n");
		printf("-------------END OF SAMLL ZONE---------------\n");
	}
	else
		printf("-----------------Small zone is empty---------------\n");

	i = 0;
	if (large)
	{
		printf("---------------------------------------------\n");
		printf("----------START OF LARGE ZONE----------------\n");
		printf("Display large zone :\n");
		while (small)
		{
			printf("Large [%d] : zone address [%p]\n", i + 1, large);
			printf("Large [%d] : zone next address [%p]\n", i + 1, large->next);
			printf("Large [%d] : zone lagest free block [%ld]\n", i + 1, large->largest_free_block_size);
			printf("-----------Blocks start----------------------\n");
			block = large->blocks;
			j = 0;
			while (block)
			{
				printf("block [%d] : block address [%p]\n", j + 1, block);
				printf("block [%d] : block next address [%p]\n", j + 1, block->next);
			printf("block [%d] : ptr addr [%p]\n", j + 1, (void *)((char *) block + (sizeof (t_block))));
				printf("block [%d] : block size [%ld] \n", j + 1, block->size);
				printf("block [%d] : block is free [%d] \n", j + 1, block->free);
				printf("block [%d] : block zone id [%d] \n", j + 1, block->zone_id);
				block = block->next;
				j++;
			}
			printf("-----------Blocks end ----------------------\n");
			large = large->next;
			i++;
		}
		printf("---------------------------------------------\n");
		printf("-------------END OF LARGE ZONE---------------\n");
	}
	else
		printf("-----------------Large zone is empty---------------\n");
		*/
}
