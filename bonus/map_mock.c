/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_mock.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 19:30:49 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 17:00:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static char	*get_grid(void)
{
	return (ft_strdup(
			"11111111111111111111"
			"10000000012222222221"
			"10111111D12111111121"
			"10122221012122222121"
			"10121121012121112121"
			"10121221012121212121"
			"10121211012121212121"
			"10121222222221212121"
			"10121111D11111212121"
			"10122222222222212121"
			"12111111111111112121"
			"12122222222222222121"
			"12121111111D11111121"
			"12121222222222222221"
			"12121211111111111111"
			"12121212222222222221"
			"12121212111111111121"
			"12122222122222222221"
			"10000N11122222222221"
			"11111111111111111111"));
}

t_map	*get_mock_map(void)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	map->height = 20;
	map->width = 20;
	map->grid = get_grid();
	if (!map->grid)
		return (free(map), NULL);
	map->door_state = ft_calloc(map->width * map->height, sizeof(double));
	if (!map->door_state)
		return (free(map->grid), free(map), NULL);
	map->door_target = ft_calloc(map->width * map->height, sizeof(double));
	if (!map->door_target)
		return (free(map->grid), free(map->door_state), free(map), NULL);
	map->no_path = ft_strdup("./textures/north.xpm");
	map->so_path = ft_strdup("./textures/south.xpm");
	map->we_path = ft_strdup("./textures/west.xpm");
	map->ea_path = ft_strdup("./textures/east.xpm");
	map->sky_path = ft_strdup("./textures/skybox.xpm");
	map->floor_color = 0x4B4B4B;
	map->ceil_color = 0x87CEEB;
	return (map);
}
