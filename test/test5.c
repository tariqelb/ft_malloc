#include <stdlib.h>


void	show_alloc_mem(void);

int main() 
{
	void *ptr;
	
	
	ptr = malloc(1024);
	ptr = malloc(1024 * 32);
	ptr = malloc(1024 * 1024);
	ptr = malloc(1024 * 1024 * 16);
	ptr = malloc(1024 * 1024 * 128);

	show_alloc_mem();

	return (0);
}

