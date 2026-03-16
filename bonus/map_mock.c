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
			"10000000010000000001"
			"10111111010111111101"
			"10100001010100000101"
			"10101101010101110101"
			"10101001010101010101"
			"10101011010101010101"
			"10101000000001010101"
			"10101111111111010101"
			"10100000000000010101"
			"10111111111111110101"
			"10100000000000000101"
			"10101111111111111101"
			"10101000000000000001"
			"10101011111111111111"
			"10101010000000000001"
			"10101010111111111101"
			"10100000100000000001"
			"10000N01000000000001"
			"11111111111111111111"));
}

static int load_texture(const t_win *win, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(win->mlxptr, path, &tex->width,
		&tex->height);
	if (!tex->img)
	{
		write(2, "Error: Failed to load texture: ", 32);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		return (1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
		&tex->line_len, &tex->endian);
	return (0);
}

// TODO: Free everything if errors happen
t_map	*get_mock_map(t_win *win)
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
	map->floor_color = 0x4B4B4B;
	map->ceil_color = 0x87CEEB;
	load_texture(win, &win->textures[0], "textures/north.xpm");
	load_texture(win, &win->textures[1], "textures/south.xpm");
	load_texture(win, &win->textures[2], "textures/west.xpm");
	load_texture(win, &win->textures[3], "textures/east.xpm");
	load_texture(win, &win->textures[4], "textures/skybox.xpm");
	load_texture(win, &win->textures[5], "textures/floor.xpm");
	return (map);
}
