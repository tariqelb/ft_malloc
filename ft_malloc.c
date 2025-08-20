#include "./ft_malloc.h"
#include <stdlib.h>

g_zone_hold g_zone_var;


void	*ft_malloc(size_t nbr_of_bytes)
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

void    ft_print_zone_info(t_zone *zone, const char *zone_name)
{
    if (!zone) 
    {
        printf("%s zone is NULL\n", zone_name);
        return;
    }

    printf("\n============= %s ZONE INFO =============\n", zone_name);
    printf("Zone pointer      : %p\n", (void *)zone);
    printf("Zone size         : %zu\n", zone->zone_size);
    printf("Largest free block: %zu\n", zone->largest_free_block_size);
    printf("t_zone struct size: %zu\n", sizeof(t_zone));
    printf("t_block struct size: %zu\n", sizeof(t_block));
    printf("----------------------------------------\n");

    t_block *block = zone->blocks;
    int i = 0;
    while (block) 
    {
        printf(" Block[%d] at %p\n", i, (void *)block);
        printf("   size : %zu\n", block->size);
        printf("   free : %d\n", block->free);
        printf("   zone_id : %d\n", block->zone_id);
        printf("   next : %p\n", (void *)block->next);
        printf("----------------------------------------\n");
        block = block->next;
        i++;
    }
}


void	ft_print_large_zone(t_zone *zone, const char *zone_name)
{
	if (!zone) 
	{
	    printf("%s zone is NULL\n", zone_name);
	    return;
	}

	while (zone != NULL)
	{
		printf("\n============= %s ZONE INFO =============\n", zone_name);
		printf("Zone pointer      : %p\n", (void *)zone);
		printf("Next Zone pointer : %p\n", (void *)zone->next);
		printf("Zone size         : %zu\n", zone->zone_size);
		printf("Largest free block: %zu\n", zone->largest_free_block_size);
		printf("t_zone struct size: %zu\n", sizeof(t_zone));
		printf("t_block struct size: %zu\n", sizeof(t_block));
		printf("----------------------------------------\n");



		t_block *block = zone->blocks;
		int i = 0;
		
		while (block) 
		{
			printf(" Block[%d] at %p\n", i, (void *)block);
			printf("   size : %zu\n", block->size);
			printf("   free : %d\n", block->free);
			printf("   zone_id : %d\n", block->zone_id);
			printf("   next : %p\n", (void *)block->next);
			printf("----------------------------------------\n");
			block = block->next;
			i++;
		}
		zone = zone->next;
	}

}

/*
int main(void)
{
	size_t	sizes[3] = {5400, 6800, 9700};
	int	i;
	char *ptrs[3];

	i = 0;

	while (i < 3)
	{
		ptrs[i] = (char *) ft_malloc(sizes[i]);
	
		if (ptrs[i] != NULL)
			printf("ptr[%d] (size %zu) address = %p\n", i, sizes[i], ptrs[i]);


		i++;
	}
	// Print state of SMALL zone after each alloc
	ft_print_large_zone(g_zone_var.large, "LARGE");
	

	i = 0;
	while (i < 3)
	{
		ft_free(ptrs[i]);
		i++;
	}
	return (0);
}
*/


int main(void)
{
	size_t sizes[5] = {63, 25, 15, 32, 5};//tiny
	//size_t sizes[5] = {200, 250, 157, 64, 512};//small
	void *ptrs[5];

	for (int i = 0; i < 5; i++) 
	{
		printf("\n>>> Allocating %zu bytes...\n", sizes[i]);
		ptrs[i] = ft_malloc(sizes[i]);
		if (ptrs[i] != NULL)
			printf("ptr[%d] (size %zu) address = %p\n", i, sizes[i], ptrs[i]);

		// Print state of SMALL zone after each alloc
		//ft_print_zone_info(g_zone_var.small, "SMALL");//small
		ft_print_zone_info(g_zone_var.tiny, "TINY");//tiny
	}

	
	// ⚠️ Don't use munmap(ptr, size) → wrong
   	// You should implement ft_free() to mark blocks free.
 	// For now, just simulate freeing:
 	for (int i = 0; i < 5; i++) 
	{
        	if (ptrs[i])
		{
            		//printf("freeing ptr[%d] %p (fake free)\n", i, ptrs[i]);
            		ft_free(ptrs[i]); // TODO: implement properly
        	}
	}

    	printf("---------------------------\n");
    	return (0);
}


