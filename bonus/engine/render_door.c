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

static void	get_door_wall_x(const t_win *win, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = win->player->pos_y + ray->perp_dist * ray->dir_y;
	else
		ray->wall_x = win->player->pos_x + ray->perp_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->wall_x = 1.0 - ray->wall_x;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->wall_x = 1.0 - ray->wall_x;
}

static int	door_dda(const t_win *win, t_ray *ray, const t_sprite *door)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (win->map->grid[ray->map_y * win->map->width + ray->map_x] == '1')
			return (1);
		if (win->map->grid[ray->map_y * win->map->width + ray->map_x] == 'D'
			&& ray->map_x == (int)door->x && ray->map_y == (int)door->y)
		{
			if (ray->side == 0)
			{
				ray->perp_dist = ray->side_dist_x - 0.5 * ray->delta_dist_x;
				if (floor(win->player->pos_y + ray->perp_dist * ray->dir_y) == ray->map_y)
					ray->hit = 1;
			}
			else
			{
				ray->perp_dist = ray->side_dist_y - 0.5 * ray->delta_dist_y;
				if (floor(win->player->pos_x + ray->perp_dist * ray->dir_x) == ray->map_x)
					ray->hit = 1;
			}
		}
	}
	get_door_wall_x(win, ray);
	return (0);
}

static void	draw_door_pixel(const t_win *win, t_ray *ray, int x_offset, int y)
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
		*(unsigned int *)(win->img->addr + (y * win->img->line_len + x_offset)) =
			color;
}

static void	draw_door_column(const t_win *win, t_ray *ray, int x)
{
	int	y;
	int	x_offset;

	y = ray->draw_start;
	x_offset = x * (win->img->bpp / 8);
	while (y < ray->draw_end)
	{
		draw_door_pixel(win, ray, x_offset, y);
		y++;
	}
}

void    render_door(const t_win *win, const t_sprite *door)
{
	t_ray	ray;
	int		x;
	int		center_ofs;
	int		orig_ceiling;
	int		pixel_offset;

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
		if (ray.perp_dist < 0.1)
			ray.perp_dist = 0.1;
		win->z_buffer[x] = ray.perp_dist;
		ray.line_height = (int)(((double)HEIGHT / 2) / ray.perp_dist);
		center_ofs = (HEIGHT / 2) + win->player->pitch;
		orig_ceiling = center_ofs - (ray.line_height / 2);
		pixel_offset = (int)(ray.line_height * door->door_offs);
		ray.draw_start = orig_ceiling - pixel_offset;
		ray.draw_end = (center_ofs + ray.line_height / 2) - pixel_offset;
		ray.tex_step = 1.0 * door->tex->height / ray.line_height;
		ray.tex_pos = 0;
		if (ray.draw_start < orig_ceiling)
		{
			ray.tex_pos += (orig_ceiling - ray.draw_start) * ray.tex_step;
			ray.draw_start = orig_ceiling;
		}
		if (ray.draw_start < 0)
		{
			ray.tex_pos += (0 - ray.draw_start) * ray.tex_step;
			ray.draw_start = 0;
		}
		if (ray.draw_end >= HEIGHT)
			ray.draw_end = HEIGHT - 1;
		if (ray.draw_start < ray.draw_end)
			draw_door_column(win, &ray, x);
		x++;
	}
}
