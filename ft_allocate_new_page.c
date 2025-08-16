#include "ft_malloc.h"


t_zone	*allocate_new_page(int zone)
{
	size_t 	page_size;
	t_zone	*temp_zone;
	
	if (zone == 0)
		page_size = 2 * g_zone_var.mapping_size; //getpagesize()
	else
		page_size = 4 * g_zone_var.mapping_size; //getpagesize()
        
	t_zone *zone = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);

        if (zone == MAP_FAILED)
        {
            perror("mmap failed");
            return (NULL);
        }

        zone->zone_size = page_size;
        zone->next = NULL;
        zone->blocks = (t_block *)((char *)zones + sizeof(t_zone));
  	zone->blocks->size = page_size - sizeof(t_zone) - sizeof(t_block);
	zone->blocks->free = 1;//free
	zone->blocks->next = NULL;
        zone->largest_free_block_size = page_size - sizeof(t_zone) - sizeof(t_block);
        
	if (temp_zone == NULL)
	{
		if (zone == 0)
			g_zone_var.tiny = zone;
		else	
			g_zone_var.small = zone;
	}
	else
	{

		if (zone == 0)
			temp_zone = g_zone_var.tiny;
		else
			temp_zone = g_zone_var.small;
		while (temp_zone->next != NULL)
			temp_zone = temp_zone->next; 
		temp_zone->next = zone;
	}
	return (zone);
}
