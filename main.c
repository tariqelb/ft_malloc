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
	char	**ptr;
	int	index;

	nbr_of_bytes	= 900;
	resize		= 950;

	ptr = (char **) malloc(sizeof(char *) * max);
	index = 0;
	printf("-------------------------ft_malloc-----------------\n");
	while (index < max)
	{
		ptr[index] = (char *) malloc( sizeof(char) * nbr_of_bytes);	
		int j = 0;
		while (j < 10)
		{
			ptr[index][j] = 'a' + j++;
		}
		ptr[index][j] = 0;
		index++;
	}

	printf("----------------------end of ft_malloc-----------------\n");
	//show_alloc_mem();

	index = 0;
	printf("-------------------------ft_realloc-----------------\n");
	while (index < max)
	{
		ptr[index] = (char *) realloc(ptr[index], resize);
		index++;
	}
	printf("-------------------------print data -----------------\n");
	index = 0;
	/*while (index < max)
	{
		write (1, ptr[index], 10);
		write(1, "\n", 1);
		index++;
	}*/
	index = 0;

	printf("--------------------end of print data-----------------\n");
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
	free(ptr);

//	while (1);
	return (0);
}
