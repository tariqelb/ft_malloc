#include "ft_malloc.h"


void	ft_show_alloc_mem(void)
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
		printf("---------------------------------------------\n");
		printf("----------START OF TINY ZONE-----------------\n");
		printf("Display tiny zone :\n");
		while (tiny)
		{
			printf("Tiny [%d] : zone address [%p]\n", i + 1, tiny);
			printf("Tiny [%d] : zone next address [%p]\n", i + 1 , tiny->next);
			printf("Tiny [%d] : zone lagest free block [%ld]\n", i + 1, tiny->largest_free_block_size);
			printf("-----------Blocks start----------------------\n");
			block = tiny->blocks;
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
			tiny = tiny->next;
			i++;
		}
		printf("---------------------------------------------\n");
		printf("-------------END OF TINY ZONE----------------\n");
	}
	else
		printf("-------------------Tiny zone is empty-------------\n");


	i = 0;
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
}
