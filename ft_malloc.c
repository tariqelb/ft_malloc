/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 19:08:35 by tel-bouh          #+#    #+#             */
/*   Updated: 2025/08/28 18:40:59 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./ft_malloc.h"

t_g_zone_hold	g_zone_var = {NULL, NULL, NULL, 0};

void	*malloc(size_t nbr_of_bytes)
{
	int	is_full;
	int	zone;
	void	*ptr;

	printf("---------------1\n");
	ptr = NULL;
	g_zone_var.mapping_size = getpagesize();
	printf("---------------1\n");
	zone = ft_choose_zone(nbr_of_bytes);
	printf("---------------2\n");
	if (zone == -1)
		return (NULL);
	else if (zone == 0 || zone == 1)
	{
	printf("---------------3\n");
		is_full = ft_check_if_zone_is_full(zone, nbr_of_bytes);
	printf("---------------4\n");
		if (is_full == 0)
			ptr = ft_find_the_best_free_block(zone, nbr_of_bytes);
		else
		{
	printf("---------------5\n");
			printf("Get here 1[%p]\n", g_zone_var.small);
			if (g_zone_var.small)
				printf("Get here 2[%p][%p]\n", g_zone_var.small, g_zone_var.small->next);
			if (ft_allocate_new_page(zone))
				ptr = ft_find_the_best_free_block(zone, nbr_of_bytes);
			printf("Get here 1[%p]\n", g_zone_var.small);
			if (g_zone_var.small)
				printf("Get here 2[%p][%p]\n", g_zone_var.small, g_zone_var.small->next);
		}
		return (ptr);
	}
	else
		return (ft_allocate_large_zone(nbr_of_bytes));
	return (ptr);
}
