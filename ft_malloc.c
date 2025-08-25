#include "./ft_malloc.h"
#include <stdlib.h>

g_zone_hold g_zone_var = {NULL, NULL, NULL, 0};


void	*malloc(size_t nbr_of_bytes)
{
	int		zone;
	int		is_full;
	void		*ptr;

	g_zone_var.mapping_size = getpagesize();
	
	zone = ft_choose_zone(nbr_of_bytes);
	if (zone == -1)	
		return (NULL);
	else if (zone == 0 || zone == 1) //0 = TINY  and 1 = SMALL
	{
		is_full = ft_check_if_zone_is_full(zone, nbr_of_bytes);
		if (is_full == 0)
		{
			ptr = ft_find_the_best_free_block(zone, nbr_of_bytes);
		}
		else
		{
			if (ft_allocate_new_page(zone))
			{
				ptr = ft_find_the_best_free_block(zone, nbr_of_bytes);
			}
		}
		return (ptr);

	}
	else //LARGE
	{
		return ft_allocate_large_zone(nbr_of_bytes);
	}
}

