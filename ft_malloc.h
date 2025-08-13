#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <pthread.h> //for mutex


//TINY: allocations up to 64 bytes
//SMALL: allocations 65 to 1024 bytes
//LARGE: allocations > 1024 bytes (own mmap)

# define TINY 64
# define SMALL 1024
# define LARGE 1024

typedef struct s_block {

    size_t              size;     // Size of the user’s data (not including this header)
    int                 free;    // 1 if block is free, 0 if it’s in use
    struct s_block      *next;  // Pointer to the next block in the zone

} t_block;


typedef struct s_zone {

        size_t          zone_size;
        struct s_zone   *next;
        t_block         *blocks;

} t_zone;

typedef struct zone_hold {
	
	t_zone	*tiny; 
	t_zone	*small;
	t_zone	*large;
	size_t	mapping_size; //page size
} g_zone_hold;

extern g_zone_hold g_zone_var;  

# endif
