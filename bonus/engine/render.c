/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:56:33 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 12:00:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	draw_wall(t_ray *ray, unsigned int *dest, int tex_x)
{
	int				tex_y;
	unsigned int	color;

	tex_y = (int)ray->tex_pos;
	if (tex_y >= ray->tex->height)
		tex_y = ray->tex->height - 1;
	ray->tex_pos += ray->tex_step;
	color = *(unsigned int *)(ray->tex->addr + (tex_y * ray->tex->line_len
				+ tex_x * (ray->tex->bpp / 8)));
	*dest = color;
}

static void	draw_line(t_win *win, t_ray *ray, int x)
{
	int				y;
	int				tex_x;
	unsigned int	*dest;
	int				line_stride;

	y = 0;
	line_stride = win->img->line_len / 4;
	dest = (unsigned int *)win->img->addr + x;
	tex_x = (int)(ray->wall_x * (double)ray->tex->width);
	if (tex_x >= ray->tex->width)
		tex_x = ray->tex->width - 1;
	if (tex_x < 0)
		tex_x = 0;
	while (y < ray->draw_start)
	{
		*dest = win->map->ceil_color;
		dest += line_stride;
		y++;
	}
	while (y < ray->draw_end)
	{
		draw_wall(ray, dest, tex_x);
		dest += line_stride;
		y++;
	}
	while (y < HEIGHT)
	{
		*dest = win->map->floor_color;
		dest += line_stride;
		y++;
	}
}

static void	get_wall(t_ray *ray, t_img *tex, t_map *map)
{
	int	pos;
	char c;

	pos = ray->map_x + (ray->map_y * map->width);
	c = map->grid[pos];
	ray->tex = &tex[c - 49];
}

static void	calculate_ray_bounds(t_win *win, t_ray *ray, int center_ofs)
{
	if (ray->perp_dist < 0.1)
		ray->perp_dist = 0.1;
	ray->line_height = (int)((double)HEIGHT / ray->perp_dist) / 2;
	ray->draw_start = center_ofs - (ray->line_height / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = center_ofs + (ray->line_height / 2);
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	get_wall(ray, win->textures, win->map);
	ray->tex_step = 1.0 * ray->tex->height / ray->line_height;
	ray->tex_pos = (ray->draw_start - center_ofs + ray->line_height / 2)
		* ray->tex_step;
}

void	render_frame(t_win *win)
{
	t_ray	ray;
	int		x;
	int		center_ofs;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(win, &ray, x);
		perform_dda(win, &ray);
		win->z_buffer[x] = ray.perp_dist;
		center_ofs = (HEIGHT / 2) + win->player->pitch;
		calculate_ray_bounds(win, &ray, center_ofs);
		draw_line(win, &ray, x);
		x++;
	}
	render_sprites(win);
	render_minimap(win->map, win->img, win);
	animate_sprites(win->sprites, get_time() * 1000, win->n_sprites);
}
