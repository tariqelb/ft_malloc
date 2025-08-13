#include "ft_malloc.h"
#include <stdlib.h>
#include <errno.h>

int main(int ac, char **av)
{
	printf("-----Test start----");

	char *ptr = NULL;
	ptr = (void*) malloc(10);
	printf("errno : %d\n", errno);
	perror("Error message ");
	if (ptr != NULL)
		free(ptr);
	else
		printf("ptr is NULL\n");
	printf("-----End start----");
	
	return (0);
}
