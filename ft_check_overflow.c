#include "ft_malloc.h"

int	ft_check_overflow(size_t nbr_of_bytes)
{
	size_t	first_bit;
	size_t	sum;
	size_t	aligned;
	size_t	header;
	int	valid;

	header = sizeof(t_zone) + sizeof(t_block);
	first_bit = nbr_of_bytes >> 63;
	valid = first_bit & 1;
	if (valid)
		return (write(2, "Error: Size too big\n", 20));
	sum = nbr_of_bytes + header;
	first_bit = sum >> 63;
	valid = first_bit & 1;
	if (valid)
		return (write(2, "Error: Size too big\n", 20));
	aligned = align16(sum);
	first_bit = aligned >> 63;
	valid = first_bit & 1;
	if (valid)
		return (write(2, "Error: Size too big\n", 20));
	return (0);
}
