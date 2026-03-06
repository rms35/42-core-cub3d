/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 17:10:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_map(const t_map *map)
{
	int	i;
	int	total;

	total = map->height * map->width;
	i = 0;
	while (i < total)
	{
		printf("%c ", map->grid[i]);
		if (i != 0 && (i + 1) % map->width == 0)
			printf("\n");
		i++;
	}
	write(1, "\n", 1);
}
