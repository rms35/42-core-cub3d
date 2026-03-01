/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:56:33 by rafael-m          #+#    #+#             */
/*   Updated: 2026/02/27 21:56:39 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static inline void	my_mlx_pixel_put(const t_img *img, const int x, const int y, const int
	color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

static inline void	set_cell(const t_img *img, const int x, const int y,
	const int
	color)
{
	int	i;
	int	j;

	// printf("x2 = %d; y2 = %d\n", x, y);
	i = 0;
	while (i < FACTOR)
	{
		j = 0;
		while (j < FACTOR)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i ++;
	}
}

void	twod_map(const t_map *map, const t_img *img)
{
	int	x;
	int	y;
	int	total;

	total = map->width * map ->height;
	x = 0;
	while (x < total)
	{
		y = 0;
		while (y < map->height)
		{
			// printf("x = %d; y = %d;x + y = %d; char = %c\n",x, y, x + y,
			// map->grid[x + y]);
			if (map->grid[x + y] == '1')
				set_cell(img,y * FACTOR, (x / map->width) * FACTOR,
					0x000000FF);
			else if (map->grid[x + y] != '0')
				set_cell(img, y * FACTOR, (x / map->width) * FACTOR, 0x00FF0000);
			if (map->grid[x + y] == '0')
				set_cell(img, y * FACTOR, (x / map->width) * FACTOR, 0x00F00FF00);
			y++;
		}
		// printf("\n");
		x += map->width;
	}
}