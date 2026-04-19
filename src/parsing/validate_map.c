/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by almorene          #+#    #+#             */
/*   Updated: 2026/04/12 00:00:00 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	fill_from(t_map *map, char *visited, int x, int y)
{
	int	idx;

	if (x < 0 || y < 0 || x >= map->width || y >= map->height)
		return (1);
	idx = (y * map->width) + x;
	if (visited[idx] || map->grid[idx] == '1')
		return (0);
	if (map->grid[idx] == ' ')
		return (1);
	visited[idx] = 1;
	if (fill_from(map, visited, x + 1, y)
		|| fill_from(map, visited, x - 1, y)
		|| fill_from(map, visited, x, y + 1)
		|| fill_from(map, visited, x, y - 1))
		return (1);
	return (0);
}

static int	validate_map_chars(const t_map *map)
{
	int	i;

	i = 0;
	while (i < map->width * map->height)
	{
		if (map->grid[i] != ' ' && map->grid[i] != '0' && map->grid[i] != '1'
			&& !ft_strchr(PLYR_DIR, map->grid[i]))
			return (error_msg("Invalid character in map"));
		i++;
	}
	return (0);
}

static int	validate_player(const t_map *map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < map->width * map->height)
	{
		if (ft_strchr(PLYR_DIR, map->grid[i]))
			count++;
		i++;
	}
	if (count != 1)
		return (error_msg("Map must contain exactly one player"));
	return (0);
}

static int	validate_map_closed(t_map *map)
{
	char	*visited;
	int		i;
	int		open_map;

	visited = ft_calloc((map->width * map->height), sizeof(char));
	if (!visited)
		return (error_msg("Memory allocation failed"));
	i = 0;
	while (i < map->width * map->height && !ft_strchr(PLYR_DIR, map->grid[i]))
		i++;
	if (i == map->width * map->height)
	{
		free(visited);
		return (error_msg("Map must contain exactly one player"));
	}
	open_map = fill_from(map, visited, i % map->width, i / map->width);
	free(visited);
	if (open_map)
		return (error_msg("Map is not closed"));
	return (0);
}

int	validate_map(t_map *map)
{
	if (validate_map_chars(map))
		return (1);
	if (validate_player(map))
		return (1);
	if (validate_map_closed(map))
		return (1);
	return (0);
}
