/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by almorene          #+#    #+#             */
/*   Updated: 2026/04/18 00:00:00 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	fill_from(t_map *map, char *visited, int x, int y, int *open_map)
{
	int	idx;

	if (*open_map)
		return ;
	if (x < 0 || y < 0 || x >= (int)map->width || y >= (int)map->height)
	{
		*open_map = 1;
		return ;
	}
	idx = (y * map->width) + x;
	if (visited[idx])
		return ;
	if (map->grid[idx] == ' ')
	{
		*open_map = 1;
		return ;
	}
	if (map->grid[idx] == '1')
		return ;
	if (map->grid[idx] != '0' && map->grid[idx] != '2' && !ft_strchr(PLYR_DIR, map->grid[idx]))
		return ;
	visited[idx] = 1;
	fill_from(map, visited, x + 1, y, open_map);
	fill_from(map, visited, x - 1, y, open_map);
	fill_from(map, visited, x, y + 1, open_map);
	fill_from(map, visited, x, y - 1, open_map);
}

static int	validate_map_chars(const t_map *map)
{
	int	i;

	i = 0;
	while (i < (int)(map->width * map->height))
	{
		if (map->grid[i] != ' ' && map->grid[i] != '0' && map->grid[i] != '1' && map->grid[i] != '2'
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
	while (i < (int)(map->width * map->height))
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
	while (i < (int)(map->width * map->height) && !ft_strchr(PLYR_DIR, map->grid[i]))
		i++;
	open_map = 0;
	if (i == (int)(map->width * map->height))
		return (free(visited), error_msg("Map must contain exactly one player"));
	fill_from(map, visited, i % map->width, i / map->width, &open_map);
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
