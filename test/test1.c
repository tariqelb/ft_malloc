#include <stdio.h>
#include <unistd.h>
#include "../ft_malloc.h"

/*void	show_alloc_mem(void)
{
	return;
}*/

int	main(void)
{
	int i = 0;
	int max = 5;
	int size = 900;
	char *ptr[max];


	printf("sum of bytes allocated : [%d] * [%d] = [%d]\n", max, size, max * size);
	sleep (2);

	while (i < max)
	{
		printf("call number %d\n", i);
		ptr[i] = malloc(900);
		i++;
	}
	show_alloc_mem();
	printf("Test end -----------------------\n");
	return (0);
}
