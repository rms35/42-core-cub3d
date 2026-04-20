/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 00:00:00 by almorene          #+#    #+#             */
/*   Updated: 2026/04/18 00:00:00 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	load_texture(const t_win *win, t_img *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(win->mlxptr, path, &tex->width,
			&tex->height);
	if (!tex->img)
	{
		write(2, "Error\nFailed to load texture: ", 30);
		write(2, path, ft_strlen(path));
		write(2, "\n", 1);
		return (1);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp,
			&tex->line_len, &tex->endian);
	if (!tex->addr)
	{
		mlx_destroy_image(win->mlxptr, tex->img);
		tex->img = NULL;
		return (error_msg("Failed to access texture data"));
	}
	return (0);
}

int	init_textures(t_win *win)
{
	if (load_texture(win, &win->textures[W1N], win->map->no_path))
		return (1);
	if (load_texture(win, &win->textures[W1S], win->map->so_path))
	{
		free_map(win->map);
		return (1);
	}
	if (load_texture(win, &win->textures[W1W], win->map->we_path))
	{
		free_map(win->map);
		return (1);
	}
	if (load_texture(win, &win->textures[W1E], win->map->ea_path))
	{
		free_map(win->map);
		return (1);
	}
	return (0);
}
