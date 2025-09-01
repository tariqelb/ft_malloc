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
	char *ptr;


//	printf("sum of bytes allocated : [%d] * [%d] = [%d]\n", max, size, max * size);

	while (i < 1024)
	{
		ptr = (char *) malloc(1024);
		ptr[0] = 42;
		i++;
	}
//	show_alloc_mem();
//	printf("Test end -----------------------\n");
	return (0);
}

/*int main()
{
	int i;
	char *addr;
	i = 0;
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		i++;
	}
	return (0);
}*/
