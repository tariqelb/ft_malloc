#include "./ft_malloc.h"
#include <stdlib.h>



//To run this main test execute those two commands
//comiple main with library ->
//gcc main.c -L. -lft_malloc -o main
//force to preload library at run time ->    
//LD_LIBRARY_PATH=$PWD LD_PRELOAD=$PWD/libft_malloc.so ./main

int	main(void)
{
	size_t	nbr_of_bytes;
	size_t	resize;
	int	max = 170;
	void	*ptr[max];
	int	index;

	nbr_of_bytes	= 900;
	resize		= 950;

	index = 0;
	printf("-------------------------ft_malloc-----------------\n");
	while (index < max)
	{
		ptr[index] = malloc(nbr_of_bytes);	
		index++;
	}

	printf("----------------------end of ft_malloc-----------------\n");
	show_alloc_mem();

	index = 0;
	printf("-------------------------ft_realloc-----------------\n");
	while (index < max)
	{
		ptr[index] = realloc(ptr[index], resize);
		index++;
	}

	printf("--------------------end of ft_realloc-----------------\n");
//	show_alloc_mem();

	index = 0;
	printf("-------------------------ft_free-----------------\n");
	while (index < max)
	{
		free(ptr[index]);
		index++;
	}
	printf("--------------------end of ft_free-----------------\n");
//	show_alloc_mem();

/*
	void	*ptr[3];

	ptr[0] = malloc(500);
	show_alloc_mem();
	ptr[1] = malloc(500);
	show_alloc_mem();
	free(ptr[1]);
	ptr[0] = realloc(ptr[0], 900);
	show_alloc_mem();
	free(ptr[0]);
	free(ptr[1]);
	show_alloc_mem();
*/
/*	void	*ptr[3];

	ptr[0] = malloc(50);
	show_alloc_mem();
	ptr[1] = malloc(19);
	show_alloc_mem();
	free(ptr[1]);
	ptr[0] = realloc(ptr[0], 31);
	show_alloc_mem();
	free(ptr[0]);
	free(ptr[1]);
	show_alloc_mem();
*/
	return (0);
}
