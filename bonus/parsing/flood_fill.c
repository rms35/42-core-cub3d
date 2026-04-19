/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 16:25:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

t_point	set_point(int x, int y)
{
	t_point	p;

	p.x = x;
	p.y = y;
	return (p);
}

void	fill_from(t_map *map, char *visited, t_point p, int *open_map)
{
	int	idx;

	if (*open_map)
		return ;
	if (p.x < 0 || p.y < 0 || p.x >= (int)map->width || p.y >= (int)map->height)
	{
		*open_map = 1;
		return ;
	}
	idx = (p.y * map->width) + p.x;
	if (visited[idx] || map->grid[idx] == '1')
		return ;
	if (map->grid[idx] == ' ')
	{
		*open_map = 1;
		return ;
	}
	visited[idx] = 1;
	fill_from(map, visited, set_point(p.x + 1, p.y), open_map);
	fill_from(map, visited, set_point(p.x - 1, p.y), open_map);
	fill_from(map, visited, set_point(p.x, p.y + 1), open_map);
	fill_from(map, visited, set_point(p.x, p.y - 1), open_map);
}
