#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../ft_malloc.h"

void print(char *s)
{
	write(1, s, strlen(s));
}

int main()
{
	char *addr;
	addr = malloc(16);

	printf("-----------------\n");
	free(NULL);
	printf("-----------------\n");
	free((void *)addr + 5);
	printf("-----------------\n");

	if (realloc((void *)addr + 5, 10) == NULL)
		print("Bonjour\n");
	printf("-----------------\n");

	return (0);
}
