/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 12:00:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	set_cell(t_img *img, size_t x, size_t y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINI_FACTOR)
	{
		j = 0;
		while (j < MINI_FACTOR)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	set_floor(t_img *img, size_t x, size_t y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINI_FACTOR)
	{
		j = 0;
		while (j < MINI_FACTOR)
		{
			if (j % 2)
				my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	set_player(t_img *img, size_t x, size_t y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < PLYR_FACTOR)
	{
		j = 0;
		while (j < PLYR_FACTOR)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	render_minimap(t_map *map, t_img *img, t_win *win)
{
	size_t	i;
	size_t	total;
	size_t	pos_x;
	size_t	pos_y;

	total = map->width * map->height;
	i = 0;
	while (i < total)
	{
		pos_x = i % map->width;
		pos_y = i / map->width;
		if (win->map->grid[i] != ' ')
			set_floor(img, pos_x * MINI_FACTOR, pos_y * MINI_FACTOR,
				win->minilu[(int)map->grid[i]]);
		i++;
	}
	set_player(img, win->player->pos_x * MINI_FACTOR,
		win->player->pos_y * MINI_FACTOR, 0x00FF0000);
}
