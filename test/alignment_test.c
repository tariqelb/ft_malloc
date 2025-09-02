#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "../ft_malloc.h"

int main()
{
	int i;
	char *addr;
	int all_aligned;
	uintptr_t aligned;

	i = 0;
	all_aligned = 1;
	
	while (i < 1024)
	{
		addr = (char*)malloc(1024);
		addr[0] = 42;
		aligned = (uintptr_t)addr;
		if (aligned % 16)
			all_aligned = 0;
		free(addr);
		i++;
	}
	if (all_aligned)
		write(1, "All address is allgined\n", 24);
	else
		write(1, "Not all address is allgined\n", 28);
	return (0);
}
