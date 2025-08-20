#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <pthread.h> //for mutex


//TINY: allocations up to 64 bytes
//SMALL: allocations 65 to 1024 bytes
//LARGE: allocations > 1024 bytes (own mmap)

# define TINY 64
# define SMALL 1023
# define LARGE 1024


#define ALIGN(x, a) (((x) + ((a) - 1)) & ~((a) - 1))  // round up to multiple of a
#define ALIGN16(x) ALIGN((x), 16)                     // shorthand for 16-byte alignment


typedef struct s_block {

 	size_t		size;     // Size of the user’s data (not including this header)
	int		free;    // 1 if block is free, 0 if it’s in use
	struct s_block	*next;  // Pointer to the next block in the zone
	int		zone_id;  // for alingment, make struct size 32
				  // know it use for indicate which zone 
				  // belong the block to simplify free operation

} __attribute__((aligned(16))) t_block;



typedef struct s_zone {

        size_t          zone_size;
        struct s_zone   *next;
        t_block         *blocks;
	size_t		largest_free_block_size;
	//Larget free block size will hold the size of largest free block , so we will reduce the search
	//operation, if there a block that can hold the required nbr of bytes we search for it.
	//if not move to the next page on the same zone
} t_zone;

typedef struct zone_hold {
	
	t_zone	*tiny; 
	t_zone	*small;
	t_zone	*large;
	size_t	mapping_size; //page size
} g_zone_hold;

extern g_zone_hold g_zone_var;  



//----ft_handle_error.c
void		ft_handle_negative_size(void);

//----ft_choose_zone.c
//Description: The function take nbr of bytes handle nigative and retun zone number that will be used to
//allocate memory , zone 0 for tiny, 1 for small and 2 for large
int     	ft_choose_zone(size_t nbr_of_bytes);

//Description: Each zone have multiple pages in real zone is a pointer for zones each zone have 2 or 4 
//pages deppending on zone size, and each zone store the size of largest free block, this function loop 
//through zone pointer and check if their a block can hold ower allocation or no, then considered as full
//if there is not suffisent free block
//return 0 on free block found and 1 on full
int		ft_check_if_zone_is_full(int zone, size_t nbr_of_bytes);

//Description : Allways we store the size of each page on zone pointer, this function loop through each 
//page and find the largest block to use it, the best block is the leagest one, for effetiontly use pages
void		*ft_find_the_best_free_block(int zone, size_t nbr_of_bytes);

//Description: Split block into two blocks if memory that block hold more that suffesent
void		*ft_resize_largest_free_block(size_t nbr_of_bytes, t_zone *page_ptr, int zone);

//Description: For pages we need always update the variable largest free block to use it later on a new allocation
void		ft_update_largest_free_block_size(t_zone *page_ptr);

//-----ft_allocate_large_zone.c
//Description: This function allacate large zone directly with mmap
void    *ft_allocate_large_zone(size_t nbr_of_bytes);


//----ft_allocate_new_page.c
//Description: Allocate new page in zones TINY and SMALL if its full
t_zone	*ft_allocate_new_page(int zone);



//---------------------------------------------------------------------

void	ft_free(void *ptr);
void	ft_merge_free_blocks(t_block *block);






# endif
