/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:56:33 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 14:00:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	draw_door_pixel(const t_win *win, t_ray *ray, const int x_offset,
	const int y)
{
	int				tex_y;
	int				tex_x;
	unsigned int	color;

	tex_y = (int)ray->tex_pos % ray->tex->height;
	if (tex_y < 0)
		tex_y += ray->tex->height;
	tex_x = (int)(ray->wall_x * (double)ray->tex->width);
	if (tex_x >= ray->tex->width)
		tex_x = ray->tex->width - 1;
	if (tex_x < 0)
		tex_x = 0;
	ray->tex_pos += ray->tex_step;
	color = *(unsigned int *)(ray->tex->addr + (tex_y * ray->tex->line_len
				+ tex_x * (ray->tex->bpp / 8)));
	if ((color & 0x00FFFFFF) != 0)
		*(unsigned int *)(win->img->addr + (y * win->img->line_len + x_offset))
			= color;
}

static void	clip_door_texture(t_ray *ray, const int orig_ceiling)
{
	if (ray->draw_start < orig_ceiling)
	{
		ray->tex_pos += (orig_ceiling - ray->draw_start) * ray->tex_step;
		ray->draw_start = orig_ceiling;
	}
	if (ray->draw_start < 0)
	{
		ray->tex_pos += (0 - ray->draw_start) * ray->tex_step;
		ray->draw_start = 0;
	}
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

static void	calc_door_params(const t_win *win, t_ray *ray, const t_sprite *door)
{
	int	center_offset;
	int	orig_ceiling;
	int	pixel_offset;

	if (ray->perp_dist < 0.1)
		ray->perp_dist = 0.1;
	ray->line_height = (int)(((double)HEIGHT / 2) / ray->perp_dist);
	center_offset = (HEIGHT / 2) + win->player->pitch;
	orig_ceiling = center_offset - (ray->line_height / 2);
	pixel_offset = (int)(ray->line_height * door->door_offs);
	ray->draw_start = orig_ceiling - pixel_offset;
	ray->draw_end = (center_offset + ray->line_height / 2) - pixel_offset;
	ray->tex_step = 1.0 * door->tex->height / ray->line_height;
	ray->tex_pos = 0;
	clip_door_texture(ray, orig_ceiling);
}

void	render_door(t_win *win, const t_sprite *door)
{
	t_ray	ray;
	int		x;
	int		x_offset;

	x = 0;
	ray.tex = win->door;
	while (x < WIDTH)
	{
		init_ray(win, &ray, x);
		if (door_dda(win, &ray, door))
		{
			x++;
			continue ;
		}
		win->z_buffer[x] = ray.perp_dist;
		calc_door_params(win, &ray, door);
		x_offset = x * (win->img->bpp / 8);
		while (ray.draw_start < ray.draw_end)
		{
			draw_door_pixel(win, &ray, x_offset, ray.draw_start);
			ray.draw_start++;
		}
		x++;
	}
}
