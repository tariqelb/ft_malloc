/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:08:51 by tel-bouh          #+#    #+#             */
/*   Updated: 2025/08/29 18:02:39 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H

# include <unistd.h>
# include <string.h>
# include <stdint.h>
# include <stdio.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <pthread.h> //for mutex
# include <errno.h>
# include <unistd.h>
# include <stdarg.h>
# include <stddef.h>

//TINY: allocations up to 64 bytes
//SMALL: allocations 65 to 131071 bytes
//LARGE: allocations >= 131072 bytes (own mmap)

# define TINY 64
# define SMALL 131071
# define LARGE 131072

typedef struct rlimit	t_rlimit;

typedef struct s_block
{
	size_t		size;
	int		free;
	int		zone_id;
	struct s_block	*next;
}	t_block;

// Size of the user’s data
// 1 if block is free, 0 if it’s in use
// Pointer to the next block in the zone
// for alingment, make struct size 32
// know it use for indicate which zone 
// belong the block to simplify free operation

typedef struct s_zone
{
	size_t		zone_size;
	t_block		*blocks;
	size_t		largest_free_block_size;
	struct s_zone	*next;
}	t_zone;

//Larget free block size will hold the size of 
//largest free block , so we will reduce the search
//operation, if there a block that can hold the 
//required nbr of bytes we search for it.
//if not move to the next page on the same zone

typedef struct zone_hold
{
	t_zone	*tiny;
	t_zone	*small;
	t_zone	*large;
	size_t	mapping_size;
}	t_g_zone_hold;

extern t_g_zone_hold	g_zone_var;

//----ft_map.c
t_zone	*ft_map(size_t alined_size);
void	*ft_return_ptr(t_block *block);
size_t	align(size_t x, size_t a);
size_t	align16(size_t x);

//----ft_handle_error.c
void	ft_handle_negative_size(void);

//----ft_choose_zone.c
//Description: The function take nbr of bytes handle
//nigative and retun zone number that will be used to
//allocate memory , zone 0 for tiny, 1 for small and 2 for large
int	ft_choose_zone(size_t nbr_of_bytes);

//Description: Each zone have multiple pages in real
//zone is a pointer for zones each zone have 2 or 4
//pages deppending on zone size, and each zone store 
//the size of largest free block, this function loop
//through zone pointer and check if their a block can
//hold ower allocation or no, then considered as full
//if there is not suffisent free block
//return 0 on free block found and 1 on full

int	ft_check_if_zone_is_full(int zone, size_t nbr_of_bytes);

//----ft_allocate_block.c
void	*ft_return_whole_block(t_block *temp_block, int zone, t_zone *page_ptr);
void	*ft_split_block(t_block *temp_block, size_t alinged_size,
			int zone, t_zone *page_ptr);

//Description : Allways we store the size of each page
//on zone pointer, this function loop through each 
//page and find the largest block to use it, the best
//block is the leagest one, for effetiontly use pages
void	*ft_find_the_best_free_block(int zone, size_t nbr_of_bytes);

//Description: Split block into two blocks if memory
//that block hold more that suffesent
void	*ft_resize_largest_free_block(size_t nbr_of_bytes,
			t_zone *page_ptr, int zone);

//Description: For pages we need always update the
//variable largest free block to use it later on a new allocation
void	ft_update_largest_free_block_size(t_zone *page_ptr);

//-----ft_allocate_large_zone.c
//Description: This function allacate large zone directly with mmap
void	*ft_allocate_large_zone(size_t nbr_of_bytes);

//----ft_allocate_new_page.c
//Description: Allocate new page in zones TINY and SMALL if its full
t_zone	*ft_allocate_new_page(int zone);

//-----------------------------------------------------
//-----ft_malloc.c
void	*malloc(size_t nbr_of_bytes);

//-----------------------------------------------------
//-----ft_free.c
void	free(void *ptr);
void	ft_merge_free_blocks(t_block *block);

//-----------------------------------------------------
//-----ft_realloc.c
void	*realloc(void *ptr, size_t size);

//-----------------------------------------------------
//-----ft_show_alloc_mem.c
void	show_alloc_mem(void);

int	ft_printf(const char *str, ...);
int	ft_put_unsignedint(unsigned int nbr);
int	ft_putint(int nbr);
int	ft_puthex(unsigned int nbr, int flag);
int	ft_putstr(char *str);
int	ft_putchar(char c);

#endif
