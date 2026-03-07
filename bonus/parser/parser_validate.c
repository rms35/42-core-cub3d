/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 23:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 23:10:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == '2' || c == 'N' || c == 'S' || c == 'E'
		|| c == 'W' || c == ' ');
}

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static int	check_neighbors(t_map *map, int x, int y)
{
	if (x == 0 || x == map->width - 1 || y == 0 || y == map->height - 1)
		return (0);
	if (map->grid[y * map->width + (x - 1)] == ' ')
		return (0);
	if (map->grid[y * map->width + (x + 1)] == ' ')
		return (0);
	if (map->grid[(y - 1) * map->width + x] == ' ')
		return (0);
	if (map->grid[(y + 1) * map->width + x] == ' ')
		return (0);
	return (1);
}

int	validate_map(t_map *map)
{
	int	x;
	int	y;
	int	p;

	p = 0;
	y = -1;
	while (++y < map->height)
	{
		x = -1;
		while (++x < map->width)
		{
			if (!is_valid_char(map->grid[y * map->width + x]))
				return (write(2, "Error: Invalid character in map\n", 29), 0);
			if (is_player(map->grid[y * map->width + x]))
				p++;
			if (map->grid[y * map->width + x] == '0'
				|| map->grid[y * map->width + x] == '2'
				|| is_player(map->grid[y * map->width + x]))
			{
				if (!check_neighbors(map, x, y))
					return (write(2, "Error: Map is not closed\n", 26), 0);
			}
		}
	}
	return (p == 1);
}
