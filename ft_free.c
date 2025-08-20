#include "ft_malloc.h"

void	ft_free(void *ptr)
{
	t_block *block;
	
	block = (t_block *) ((char *)ptr - sizeof(t_block));
	block->free = 1;

	printf("Pointer addr : [%p]\n", ptr);
	ft_merge_free_blocks(block);
	return;
}


void	ft_merge_free_blocks(t_block *block)
{
	//this fuction merge two continuous free block on zone tiny and small
	//and free the zone if the block on large zone

	t_zone *temp_zone;

	if (block->zone_id == 0 || block->zone_id == 1)
	{
		temp_zone = g_zone_var.tiny;
		if (block->zone_id == 1)
			temp_zone = g_zone_var.small;

		printf("Free zone [%d]:\n", block->zone_id);
		printf("Block addr [%p]:\n", block);
		t_block *curr = temp_zone->blocks;
		while (curr && curr->next)
		{
    			if (curr->free && curr->next->free) 
			{
        			curr->size += sizeof(t_block) + curr->next->size;
        			curr->next = curr->next->next;
    			} 
			else
			{
        			curr = curr->next;
    			}
		}
	}
	else if (block->zone_id == 2)
	{
		t_zone *prev = NULL;
		t_zone *curr = g_zone_var.large;

		while (curr) 
		{
			if (curr->blocks->free)
			{
				if (prev)
			    		prev->next = curr->next;
				else
			    		g_zone_var.large = curr->next;

				printf("Block addr %p\n", block);
				printf("Free large zone ptr : %p\n", curr);
				munmap(curr, curr->zone_size);
				return;
		    	}
		    prev = curr;
		    curr = curr->next;
		}
	}
}

