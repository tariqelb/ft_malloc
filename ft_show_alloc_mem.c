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
	printf("---------------------------------------------\n");
	printf("----------START OF TINY ZONE-----------------\n");
	printf("Display tiny zone :");
	while (tiny)
	{
		printf("Tiny [%d] : zone address [%p]\n", i, tiny);
		printf("Tiny [%d] : zone next address [%d]\n", i, tiny->next);
		printf("Tiny [%d] : zone lagest free block [%ld]\n", i, tiny->largest_free_block_size);
		printf("-----------Blocks----------------------\n");
		block = tiny->blocks;
		j = 0;
		while (block)
		{
			printf("block [%d] : block address [%p]\n", j, block);
			printf("block [%d] : block next address [%p]\n", j, block->next);
			printf("block [%d] : block size [%ld] \n", j, block->size);
			printf("block [%d] : block is free [%d] \n", j, block->free);
			printf("block [%d] : block zone id [%d] \n", j, block->zone_id);
			block = block->next;
			j++;
		}
		tiny = tiny->next;
		i++;
	}
	printf("---------------------------------------------\n");
	printf("-------------END OF TINY ZONE----------------\n");



	i = 0;
	printf("---------------------------------------------\n");
	printf("----------START OF SMALL ZONE----------------\n");
	printf("Display small zone :");
	while (tiny)
	{
		printf("Small [%d] : zone address [%p]\n", i, small);
		printf("Small [%d] : zone next address [%d]\n", i, small->next);
		printf("Small [%d] : zone lagest free block [%ld]\n", i, small->largest_free_block_size);
		printf("-----------Blocks----------------------\n");
		block = small->blocks;
		j = 0;
		while (block)
		{
			printf("block [%d] : block address [%p]\n", j, block);
			printf("block [%d] : block next address [%p]\n", j, block->next);
			printf("block [%d] : block size [%ld] \n", j, block->size);
			printf("block [%d] : block is free [%d] \n", j, block->free);
			printf("block [%d] : block zone id [%d] \n", j, block->zone_id);
			block = block->next;
			j++;
		}
		small = small->next;
		i++;
	}
	printf("---------------------------------------------\n");
	printf("-------------END OF SAMLL ZONE---------------\n");



	i = 0;
	printf("---------------------------------------------\n");
	printf("----------START OF LARGE ZONE----------------\n");
	printf("Display large zone :");
	while (tiny)
	{
		printf("Large [%d] : zone address [%p]\n", i, tiny);
		printf("Large [%d] : zone next address [%d]\n", i, tiny->next);
		printf("Large [%d] : zone lagest free block [%ld]\n", i, tiny->largest_free_block_size);
		printf("-----------Blocks----------------------\n");
		block = large->blocks;
		j = 0;
		while (block)
		{
			printf("block [%d] : block address [%p]\n", j, block);
			printf("block [%d] : block next address [%p]\n", j, block->next);
			printf("block [%d] : block size [%ld] \n", j, block->size);
			printf("block [%d] : block is free [%d] \n", j, block->free);
			printf("block [%d] : block zone id [%d] \n", j, block->zone_id);
			block = block->next;
			j++;
		}
		large = large->next;
		i++;
	}
	printf("---------------------------------------------\n");
	printf("-------------END OF LARGE ZONE---------------\n");

}
