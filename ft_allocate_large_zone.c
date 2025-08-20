#include "ft_malloc.h"

void	*ft_allocate_large_zone(size_t nbr_of_bytes)
{
	//Allocate large zone directly with mmap
	 t_zone	*temp_zone;
	 t_zone *zone;
	 
	 size_t total_size = sizeof(t_zone) + sizeof(t_block) + nbr_of_bytes;
	 size_t aligned_size = ALIGN16(total_size);  
	 zone = mmap(NULL, aligned_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

	if (zone == MAP_FAILED)
	{
		perror("mmap failed: ");
		return (NULL);
	}
	
	zone->zone_size = total_size;
	zone->next = NULL;
	zone->blocks = (t_block *)((char *)zone + sizeof(t_zone));

	t_block *block = zone->blocks;

   	block->size = aligned_size - sizeof(t_zone) - sizeof(t_block);
   	block->free = 0;
   	block->next = NULL;
   	block->zone_id = 2;
	
	if (g_zone_var.large == NULL)
		g_zone_var.large = zone;
	else
	{
		temp_zone = g_zone_var.large;
		while (temp_zone->next != NULL)
			temp_zone = temp_zone->next;
		temp_zone->next = zone;	
	}
	return ((void *) ((char *)block + sizeof(t_block)));
}
