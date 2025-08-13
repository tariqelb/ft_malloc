#include "./ft_malloc.h"

g_zone_hold g_zone_var;


void	*ft_handle_zero_bytes()
{
	perror("Error message ");
	return ((void*) 0);
}

int	ft_allocate_tiny_page()
{
	
	size_t page_size = 2 * g_zone_var.mapping_size; //getpagesize() 
	t_zone *zones = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	
	if (zones == MAP_FAILED) 
	{
	    perror("mmap failed");
	    return (1);
	}

	zones.zone_size = page_size;
	zone.blocks = (t_block *)((char *)zones + sizeof(t_zone));

	p_zone_var.tiny = zones;
	
	return (0);
}

void	*ft_handle_zero_bytes()
{
	int map_error = 0;

	if (g_zone_var_tiny == NULL)
	{
		map_error = ft_allocate_tiny_page();
		if (map_error)
			return (NULL);
	}
	else
	{
	}
}


void	*ft_malloc(size_t nbr_of_bytes)
{
	if (nbr_of_bytes < 0)
		return ft_handle_negative_bytes();
	else if (nbr_of_bytes == 0)
		ft_handle_zero_bytes();
	else if (nbr_of_bytes <= TINY)
		ft_allocate_tiny_chunk(nbr_of_bytes);
	else if (nbr_of_bytes < SMALL)
		ft_allocate_small_chunk(nbr_of_bytes);
	else if (nbr_of_bytes >= 1024)
		ft_allocate_large_chunk(nbr_of_bytes);
	return ((void *)0);
}


int main(int ac, char **av)
{

	g_zone_var.tiny = NULL;
	g_zone_var.small = NULL;
	g_zone_var.large = NULL;
	g_zone_var.mapping_size = getpagesize();
	
	t_zone *zones;
	//t_zone *zones = mmap(NULL, 2, PROT_READ | PROT_WRITE,
         //           MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	
	
	//if (zones == MAP_FAILED) {
	//    perror("mmap failed");
	//    return 1;
	//}

	// Initialize the zone structure
	zones->zone_size = g_zone_var.mapping_size - sizeof(t_zone); // Subtract header size
	zones->next = NULL;
	// First block starts after zone header
	zones->blocks = (t_block*)((char*)zones + sizeof(t_zone));

	// Initialize the first block
	t_block *first_block = zones->blocks;
	first_block->size = zones->zone_size - sizeof(t_block); // Subtract block header size
	first_block->free = 1;
	first_block->next = NULL;

	printf("Total size of the mapped pages: %ld\n", g_zone_var.mapping_size);
	printf("Zone header info:\n");
	printf("  zone_size: %ld\n", zones->zone_size);
	printf("  next zone: %p\n", (void*)zones->next);
	printf("  first block: %p\n", (void*)zones->blocks);
	printf("First block info:\n");
	printf("  size: %ld\n", first_block->size);
	printf("  free: %d\n", first_block->free);
	printf("  next: %p\n", (void*)first_block->next);

	return (0);
}
