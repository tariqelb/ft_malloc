#include "ft_malloc.h"


void	*realloc(void *ptr, size_t size)
{
	t_block	*block;
	t_block	*new_block;
	size_t	aligned_size;
	int	zone;
	void	*new_ptr;

    	if (!ptr)
        	return malloc(size);
 	if (size == 0)
	{	
        	free(ptr);
        	return (NULL);
    	}
	block = (t_block *)((char *) ptr - sizeof(t_block));
	aligned_size = ALIGN16(size);
	
	if (block->size >= aligned_size)
		return (ptr);

	zone = ft_choose_zone(size);
	if (zone == 2 || zone != block->zone_id) 
	{
        	new_ptr = malloc(size);
        	if (!new_ptr)
			return NULL;
        	memcpy(new_ptr, ptr, block->size);
        	free(ptr);
        	return (new_ptr);
 	}

	//if requested bytes less than block size and also the aligned block
	if (block->size >= aligned_size)
	{
		size_t excess = block->size - aligned_size;

    		if (excess >= sizeof(t_block) + 16) 
		{ 
        		// split and create a new free block
        		new_block = (t_block *)((char *)block + sizeof(t_block) + aligned_size);
        		new_block->size = excess - sizeof(t_block);
        		new_block->free = 1;
        		new_block->next = block->next;
        		new_block->zone_id = block->zone_id;

        		block->size = aligned_size;
        		block->next = new_block;
    		}
   		return (ptr);
	}
	//check if next block is free and have the number of bytes needed
	if (block->next && block->next->free == 1)
	{
		printf(" first here ....\n");
		size_t total = block->size + sizeof(t_block) + block->next->size;
		if (aligned_size <= total)
		{
			size_t remainder = total - aligned_size;

			if (remainder >= sizeof(t_block) + 1)//normmaly the split should be if remain bytes can
							     //create the minimum block which is sizeof(t_block)
							     //+ 16 , not 1 bytes , its ok
			{
				// Split: place a new header after the expanded payload
				t_block *new_block = (t_block *)((char *)block + sizeof(t_block) + aligned_size);
				new_block->size   = remainder - sizeof(t_block); // payload of the remainder
				new_block->free   = 1;
				new_block->zone_id = block->zone_id;
				new_block->next   = block->next->next;

				block->size = aligned_size;
				block->next = new_block;
				// block->free should already be 0
			} 
			else 
			{
				// Use both blocks entirely (no split)
				// merged blocks size
				block->size = total;
				block->next = block->next->next;
				// block->free = 0; // already allocated
			}
		}
		return (ptr);
	}
	new_ptr = malloc(size);
   	if (!new_ptr)
        	return NULL;
 	size_t to_copy = block->size < aligned_size ? block->size : aligned_size;
 	memcpy(new_ptr, ptr, to_copy);
 	free(ptr);
    		return (new_ptr);
}



