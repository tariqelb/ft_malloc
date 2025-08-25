#include "./ft_malloc.h"
#include <stdlib.h>


/*
int main(void)
{

	printf("-----------------start of ft_malloc--------------\n");
	printf("page size : [%d]\n", getpagesize());


	//tiny
	size_t	sizes[5] = {3, 5, 6, 7, 4};
	int	max = 105;
	void	*ptrs[max];
	int	nbr_of_bytes = 900;
	for (int i = 0; i < max; i++) 
	{
//		printf("\n>>> Allocating %d bytes...\n", nbr_of_bytes);
		ptrs[i] = malloc(nbr_of_bytes);
//		if (ptrs[i] != NULL)
//			printf("ptr[%d] (size %d) address = %p\n", i, nbr_of_bytes, ptrs[i]);
//		else
//			printf("PTR return null \n");

	}
	printf("NULL : %p\n", g_zone_var.small);
	ft_show_alloc_mem();
	
 	for (int i = 0; i < max; i++) 
	{
        	if (ptrs[i])
		{
		//	printf ("index [%d]  : ", i);
            		free(ptrs[i]);
        	}
	}

    	printf("---------------------------\n");
	//ft_print_zone_info(g_zone_var.small, "SMALL");//tiny
	ft_show_alloc_mem();
    	return (0);
}
*/
int	main(void)
{
/*	size_t	nbr_of_bytes;
	size_t	resize;
	int	max = 70;
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
	ft_show_alloc_mem();

	index = 0;
	printf("-------------------------ft_realloc-----------------\n");
	while (index < max)
	{
		ptr[index] = realloc(ptr[index], resize);
		index++;
	}

	printf("--------------------end of ft_realloc-----------------\n");
	ft_show_alloc_mem();

	index = 0;
	printf("-------------------------ft_free-----------------\n");
	while (index < max)
	{
		free(ptr[index]);
		index++;
	}
	printf("--------------------end of ft_free-----------------\n");
	ft_show_alloc_mem();
*/
	/*
	void	*ptr[3];

	ptr[0] = malloc(500);
	ft_show_alloc_mem();
	ptr[1] = malloc(500);
	ft_show_alloc_mem();
	free(ptr[1]);
	realloc(ptr[0], 900);
	ft_show_alloc_mem();
	free(ptr[0]);
	free(ptr[1]);
	ft_show_alloc_mem();
*/
	int i = 0;
	void	*ptr[100];
	while (i < 100)
	{
		printf("index [%d] \n", i);
		ptr[i] = malloc(184467440737095516);
		i++;
	}
	i = 0;
	while (i < 100)
	{
		free(ptr[i]);
		i++;
	}
	return (0);
}
