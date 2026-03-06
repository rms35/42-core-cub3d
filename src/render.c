/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:56:33 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 18:25:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_tex_line(const t_win *win, const t_ray *ray, int x, t_img *tex)
{
	int		y;
	int		ty;
	double	step;
	double	pos;
	int		tx;

	if (ray->side == 0)
		tx = (int)((win->player->pos_y + ray->perp_wall_dist * ray->dir_y)
				* 64.0) % 64;
	else
		tx = (int)((win->player->pos_x + ray->perp_wall_dist * ray->dir_x)
				* 64.0) % 64;
	step = 1.0 * 64 / ray->line_height;
	pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		ty = (int)pos & 63;
		pos += step;
		*(unsigned int *)(win->img->addr + (y * win->img->line_len + x * 4))
			= *(unsigned int *)(tex->addr + (ty * tex->line_len + tx * 4));
		y++;
	}
}

static void	fill_floor_ceil(const t_win *win, const t_ray *ray, int x)
{
	int	y;

	y = 0;
	while (y < ray->draw_start)
	{
		*(unsigned int *)(win->img->addr + (y * win->img->line_len + x * 4))
			= win->map->ceil_color;
		y++;
	}
	y = ray->draw_end + 1;
	while (y < HEIGHT)
	{
		*(unsigned int *)(win->img->addr + (y * win->img->line_len + x * 4))
			= win->map->floor_color;
		y++;
	}
}

static void	render_wall(const t_win *win, const t_ray *ray, const int x)
{
	t_img	*tex;

	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			tex = (t_img *)&win->tex[3];
		else
			tex = (t_img *)&win->tex[2];
	}
	else
	{
		if (ray->dir_y > 0)
			tex = (t_img *)&win->tex[1];
		else
			tex = (t_img *)&win->tex[0];
	}
	draw_tex_line(win, ray, x, tex);
}

void	render_frame(const t_win *win)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(win, &ray, x);
		perform_dda(win, &ray);
		ray.line_height = (int)(HEIGHT / ray.perp_wall_dist);
		ray.draw_start = -ray.line_height / 2 + HEIGHT / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = ray.line_height / 2 + HEIGHT / 2;
		if (ray.draw_end >= HEIGHT)
			ray.draw_end = HEIGHT - 1;
		fill_floor_ceil(win, &ray, x);
		render_wall(win, &ray, x);
		x++;
	}
}
