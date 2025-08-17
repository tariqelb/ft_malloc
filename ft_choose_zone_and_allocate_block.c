#include "ft_malloc.h"


int	ft_choose_zone(size_t nbr_of_bytes)
{
	int zone = -1;

        if (nbr_of_bytes >= 0 && nbr_of_bytes <= TINY)
        	return (0);     
        else if (nbr_of_bytes > TINY && nbr_of_bytes <= SMALL )
		return (1);
        else if (nbr_of_bytes >= 1024)
		return (2);
	return (zone);
}

int	ft_check_if_zone_is_full(int zone, size_t nbr_of_bytes)
{
	t_zone	*temp_zone;
	int		is_full;	
	int 	size;
	
	size = nbr_of_bytes + sizeof(t_block);
	is_full = 1;

	if (zone == 0)
		temp_zone = g_zone_var.tiny;
	else //if (zone == 1)
		temp_zone = g_zone_var.small;

	while (temp_zone != NULL)
	{
		if (temp_zone->largest_free_block_size >= size)
		    return (0);
		temp_zone = temp_zone->next;	
	}
	return (is_full);
}



void	*ft_find_the_best_free_block(int zone, size_t nbr_of_bytes)
{
	//This funtion loop through zones and find the largest free block
	t_zone	*temp_zone;
	t_block	*best_free_block;

	if (zone == 0)
		temp_zone = g_zone_var.tiny;
	else
		temp_zone = g_zone_var.small;

	best_free_block = NULL;
	
	while (temp_zone != NULL)
	{
		if (temp_zone->largest_free_block_size >= nbr_of_bytes)
		{
			best_free_block = ft_resize_largest_free_block(nbr_of_bytes, temp_zone);
			//Get only required bytes and create new block with the remain bytes
			//if the remain bytes enough to create new block, otherwise return the whole block
		}
		temp_zone = temp_zone->next;
	}
	return (best_free_block);
}

void *ft_resize_largest_free_block(size_t nbr_of_bytes, t_zone *page_ptr)
{
    t_block *temp_block;
    t_block *new_block;
    size_t  largest_free_block;
    size_t  aligned_size;

    aligned_size = ALIGN16(nbr_of_bytes);  // round user request to multiple of 16
    largest_free_block = page_ptr->largest_free_block_size;
    temp_block = page_ptr->blocks;

    while (temp_block != NULL)
    {
        if (temp_block->free == 1 && temp_block->size == largest_free_block)
        {
            if (temp_block->size - aligned_size >= sizeof(t_block) + 1)
            {
                // create a new block in the leftover space
                new_block = (t_block *)((char *)temp_block + sizeof(t_block) + aligned_size);
                new_block->next = temp_block->next;
                new_block->size = temp_block->size - aligned_size - sizeof(t_block);
                new_block->free = 1;

                temp_block->next = new_block;
                temp_block->size = aligned_size;
                temp_block->free = 0;

                ft_update_largest_free_block_size(page_ptr);

                return (void *)((char *)temp_block + sizeof(t_block));
            }
            else
            {
                // not enough room for a split, give entire block
                ft_update_largest_free_block_size(page_ptr);
                temp_block->free = 0;

                return (void *)((char *)temp_block + sizeof(t_block));
            }
        }
        temp_block = temp_block->next;
    }
    return NULL;
}

void	ft_update_largest_free_block_size(t_zone *page_ptr)
{
	int 	new_size;
	t_block *temp_block;

	temp_block = page_ptr->blocks;
	new_size = 0;
	while (temp_block != NULL)
	{
		if (temp_block->free)
		{
			if (temp_block->size > new_size)
				new_size = temp_block->size;
		}	
		temp_block = temp_block->next;
	}
	page_ptr->largest_free_block_size = new_size;
}


