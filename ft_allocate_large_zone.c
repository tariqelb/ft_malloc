#include "ft_malloc.h"


static int ft_add_overflow_size(size_t a, size_t b, size_t *out) 
{
    return __builtin_add_overflow(a, b, out);
}


void	*ft_allocate_large_zone(size_t nbr_of_bytes)
{
	//Allocate large zone directly with mmap
	t_zone	*temp_zone;
	t_zone *zone;
	 
	size_t	total_size = sizeof(t_zone) + sizeof(t_block);
	size_t	total;
	size_t	aligned_size;  
	struct	rlimit lim;

	//check if total size overflow size_t max;
	if (ft_add_overflow_size(total_size, nbr_of_bytes, &total))
	{
		errno = ENOMEM;
		perror("Large number > size_t : ");
		return (NULL);
	}

	aligned_size = ALIGN16(total);
    	//check if adding alignment to total overflow the size_t max size
	//when overflow happen the result will be less that total
	if (aligned_size < total) 
	{
        	errno = ENOMEM;
		perror("Large number > size_t : ");
        	return NULL;
    	}

	getrlimit(RLIMIT_AS, &lim);
	if (aligned_size > lim.rlim_cur)
	{
		perror("Limit error : ");
    		return NULL;
	}

	//The actual RAM memory available is around 64 GB but the kernel tell 
	//a process you can have more arount 128TIB in 64 architecture, those called soft and hard limit
	//soft limit is how mutch a process can have and hard limit is how soft limit could rise
	//how that can happen, this related to concept of paging in RAM only needed (active) pages been in RAM 
	//and non-active pages moved to swap or deleted , that how we achieve move that phusucal RAM
	if (getrlimit(RLIMIT_AS, &lim) == 0 && lim.rlim_cur != RLIM_INFINITY)
	{
		if ((unsigned long long)aligned_size > (unsigned long long)lim.rlim_cur) 
		{
			errno = ENOMEM;
			perror("Limit error : ");
			return NULL;
		}
	}
	else
	{
		const size_t MAX_VA_CONSERVATIVE = (size_t)1ULL << 47; // ~128 TiB
		if (aligned_size > MAX_VA_CONSERVATIVE)
		{
			errno = ENOMEM;
			perror("Limit error : ");
			return NULL;
		}
	}

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
