#include "ft_malloc.h"

void	ft_handle_negative_size(void)
{
	write (2, "Cannot allocate memory.", 23);
	return;
}
