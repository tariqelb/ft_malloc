#include <stdio.h>
#include <unistd.h>
#include "../ft_malloc.h"

int	main(void)
{
	int i = 0;
	int max = 1024;
	char *ptr;

	while (i < max)
	{
		ptr = (char *) malloc(1024);
		ptr[0] = 42;
		i++;
	}
	return (0);
}

