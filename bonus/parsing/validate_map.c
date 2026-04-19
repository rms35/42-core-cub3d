/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by almorene          #+#    #+#             */
/*   Updated: 2026/04/19 16:05:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	is_valid_char(char c)
{
	if (c == ' ' || c == '0' || c == '1' || c == '2' || c == 'F' || c == 'D')
		return (1);
	if (ft_strchr(PLYR_DIR, c) || ft_strchr(WALLS, c))
		return (1);
	return (0);
}

static int	validate_map_chars(t_map *map)
{
	int	i;
	int	total;

	total = (int)(map->width * map->height);
	i = 0;
	while (i < total)
	{
		if (!is_valid_char(map->grid[i]))
			return (error_msg("Invalid character in map"));
		i++;
	}
	return (0);
}

static int	validate_player(t_map *map)
{
	int	i;
	int	count;
	int	total;

	total = (int)(map->width * map->height);
	i = 0;
	count = 0;
	while (i < total)
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
	int		total;

	total = (int)(map->width * map->height);
	visited = ft_calloc(total, sizeof(char));
	if (!visited)
		return (error_msg("Memory allocation failed"));
	i = 0;
	while (i < total && !ft_strchr(PLYR_DIR, map->grid[i]))
		i++;
	open_map = 0;
	if (i == total)
	{
		free(visited);
		return (error_msg("Map must contain exactly one player"));
	}
	fill_from(map, visited, set_point(i % (int)map->width,
			i / (int)map->width), &open_map);
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
