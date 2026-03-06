/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 18:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 18:10:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int	apply_fog(unsigned int color, double dist)
{
	double	f;
	int		rgb[3];

	f = 1.0 / (1.0 + dist * dist * 0.05);
	if (f > 1.0)
		f = 1.0;
	rgb[0] = (((color >> 16) & 0xFF) * f) + (0x1a * (1.0 - f));
	rgb[1] = (((color >> 8) & 0xFF) * f) + (0x1b * (1.0 - f));
	rgb[2] = ((color & 0xFF) * f) + (0x26 * (1.0 - f));
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	render_floor(const t_win *win, const t_ray *ray, const int x)
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
			= apply_fog(*(unsigned int *)(win->tex[4].addr + (ty * 256
						+ tx * 4)), dist);
	}
}

void	render_ceil(const t_win *win, const t_ray *ray, int x)
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
			= apply_fog(*(unsigned int *)(win->tex[5].addr + (ty * 256
						+ tx * 4)), dist);
	}
}
