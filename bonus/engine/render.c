/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:56:33 by rafael            #+#    #+#             */
/*   Updated: 2026/04/20 12:00:00 by rafael           ###   ########.fr       */
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

static void	draw_background(const t_win *win, int x, int start, int end)
{
	int				y;
	int				line_stride;
	unsigned int	*dest;

	line_stride = win->img->line_len / 4;
	dest = (unsigned int *)win->img->addr + x;
	y = 0;
	while (y < start)
	{
		dest[y * line_stride] = win->map->ceil_color;
		y++;
	}
	y = end;
	while (y < HEIGHT)
	{
		dest[y * line_stride] = win->map->floor_color;
		y++;
	}
}

static void	draw_line(const t_win *win, t_ray *ray, int x)
{
	int				y;
	int				tex_x;
	int				line_stride;
	unsigned int	*dest;

	line_stride = win->img->line_len / 4;
	draw_background(win, x, ray->draw_start, ray->draw_end);
	dest = (unsigned int *)win->img->addr + x;
	tex_x = (int)(ray->wall_x * (double)ray->tex->width);
	if (tex_x >= ray->tex->width)
		tex_x = ray->tex->width - 1;
	if (tex_x < 0)
		tex_x = 0;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		draw_wall(ray, &dest[y * line_stride], tex_x);
		y++;
	}
}

static void	calculate_ray_bounds(t_win *win, t_ray *ray, int center_ofs)
{
	int	pos;

	if (ray->perp_dist < 0.1)
		ray->perp_dist = 0.1;
	ray->line_height = (int)((double)HEIGHT / ray->perp_dist) / 2;
	ray->draw_start = center_ofs - (ray->line_height / 2);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = center_ofs + (ray->line_height / 2);
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	pos = ray->map_x + (ray->map_y * win->map->width);
	ray->tex = &win->textures[win->map->grid[pos] - 49];
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
