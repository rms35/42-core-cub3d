/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 18:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 19:10:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

unsigned int	apply_fog(unsigned int color, double d, double p)
{
	double	f;
	int		rgb[3];

	f = 1.0 / (1.0 + d * d * 0.05);
	if (f > 1.0)
		f = 1.0;
	rgb[0] = (int)((color >> 16 & 0xFF) * p);
	rgb[1] = (int)((color >> 8 & 0xFF) * p);
	rgb[2] = (int)((color & 0xFF) * p);
	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
	rgb[0] = (rgb[0] * f) + (0x1a * (1.0 - f));
	rgb[1] = (rgb[1] * f) + (0x1b * (1.0 - f));
	rgb[2] = (rgb[2] * f) + (0x26 * (1.0 - f));
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	render_floor(const t_win *win, const t_ray *ray, int x, double p)
{
	int		y;
	double	d;
	int		tx;
	int		ty;

	y = ray->draw_end;
	while (++y < HEIGHT)
	{
		d = HEIGHT / (2.0 * y - HEIGHT);
		tx = (int)(64 * (win->player->pos_x + d * ray->dir_x)) % 64;
		ty = (int)(64 * (win->player->pos_y + d * ray->dir_y)) % 64;
		if (tx < 0)
			tx += 64;
		if (ty < 0)
			ty += 64;
		*(unsigned int *)(win->img->addr + (y * win->img->line_len + x * 4))
			= apply_fog(*(unsigned int *)(win->tex[4].addr + (ty * 256
						+ tx * 4)), d, p);
	}
}

void	render_ceil(const t_win *win, const t_ray *ray, int x, double p)
{
	int		y;
	double	d;
	int		tx;
	int		ty;

	y = -1;
	while (++y < ray->draw_start)
	{
		d = HEIGHT / (HEIGHT - 2.0 * y);
		tx = (int)(64 * (win->player->pos_x + d * ray->dir_x)) % 64;
		ty = (int)(64 * (win->player->pos_y + d * ray->dir_y)) % 64;
		if (tx < 0)
			tx += 64;
		if (ty < 0)
			ty += 64;
		*(unsigned int *)(win->img->addr + (y * win->img->line_len + x * 4))
			= apply_fog(*(unsigned int *)(win->tex[5].addr + (ty * 256
						+ tx * 4)), d, p);
	}
}
