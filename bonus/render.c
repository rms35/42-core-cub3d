/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:56:33 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 17:20:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_tex_line(const t_win *win, const t_ray *ray, int x, const t_img
	*tex)
{
	int		y;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		tex_x;

	if (ray->side == 0)
		tex_x = (int)((win->player->pos_y + ray->perp_wall_dist * ray->dir_y)
				* 64.0) % 64;
	else
		tex_x = (int)((win->player->pos_x + ray->perp_wall_dist * ray->dir_x)
				* 64.0) % 64;
	step = 1.0 * 64 / ray->line_height;
	tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos & (64 - 1);
		tex_pos += step;
		*(unsigned int *)(win->img->addr + (y * win->img->line_len + x * 4))
			= *(unsigned int *)(tex->addr + (tex_y *
				tex->line_len + tex_x * 4));
		y++;
	}
}

static void	render_floor(const t_win *win, const t_ray *ray, const int x)
{
	int		y;
	double	dist;
	int		tx;
	int		ty;

	y = ray->draw_end;
	while (++y < HEIGHT)
	{
		dist = HEIGHT / (2.0 * y - HEIGHT);
		tx = (int)(64 * (win->player->pos_x + dist * ray->dir_x)) % 64;
		ty = (int)(64 * (win->player->pos_y + dist * ray->dir_y)) % 64;
		if (tx < 0)
			tx += 64;
		if (ty < 0)
			ty += 64;
		*(unsigned int *)(win->img->addr + (y * win->img->line_len + x * 4))
			= *(unsigned int *)(win->tex[4].addr + (ty * 256 + tx * 4));
	}
}

static void	render_ceil(const t_win *win, t_ray *ray, int x)
{
	int		y;
	double	dist;
	int		tx;
	int		ty;

	y = -1;
	while (++y < ray->draw_start)
	{
		dist = HEIGHT / (HEIGHT - 2.0 * y);
		tx = (int)(64 * (win->player->pos_x + dist * ray->dir_x)) % 64;
		ty = (int)(64 * (win->player->pos_y + dist * ray->dir_y)) % 64;
		if (tx < 0)
			tx += 64;
		if (ty < 0)
			ty += 64;
		*(unsigned int *)(win->img->addr + (y * win->img->line_len + x * 4))
			= *(unsigned int *)(win->tex[5].addr + (ty * 256 + tx * 4));
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
		render_floor(win, &ray, x);
		render_ceil(win, &ray, x);
		render_wall(win, &ray, x);
		x++;
	}
}
