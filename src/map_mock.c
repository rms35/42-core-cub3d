/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:30:49 by rafael            #+#    #+#             */
/*   Updated: 2026/02/27 20:49:02 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

t_map	*get_mock_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->height = 6;
	map->width = 6;
	map->grid = malloc(sizeof(char) * (map->width * map->height + 1));
	if (!map->grid)
		return (free(map), NULL);
	ft_memcpy(map->grid, "111111" "100001" "101001" "100001" "10N001"
		"111111", 36);
	map->grid[36] = '\0';
	map->no_path = ft_strdup("./textures/north.xpm");
	map->so_path = ft_strdup("./textures/south.xpm");
	map->we_path = ft_strdup("./textures/west.xpm");
	map->ea_path = ft_strdup("./textures/east.xpm");
	map->floor_color = 0x4B4B4B;
	map->ceil_color = 0x87CEEB;
	return (map);
}
