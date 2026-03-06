/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 18:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 22:30:00 by rafael           ###   ########.fr       */
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
	rgb[0] = (int)((color >> 16 & 0xFF) * p * f + 0x1a * (1.0 - f));
	rgb[1] = (int)((color >> 8 & 0xFF) * p * f + 0x1b * (1.0 - f));
	rgb[2] = (int)((color & 0xFF) * p * f + 0x26 * (1.0 - f));
	if (rgb[0] > 255)
		rgb[0] = 255;
	if (rgb[1] > 255)
		rgb[1] = 255;
	if (rgb[2] > 255)
		rgb[2] = 255;
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

void	render_env(const t_win *win, const t_ray *ray, int x, double p[2])
{
	int		y;
	double	d;
	int		t[2];

	y = -1;
	while (++y < HEIGHT)
	{
		if (y >= ray->draw_start && y <= ray->draw_end)
			continue ;
		d = (double)HEIGHT / fabs(HEIGHT - 2.0 * (y - win->player->pitch));
		t[0] = (int)(64 * (win->player->pos_x + d * ray->dir_x)) & 63;
		t[1] = (int)(64 * (win->player->pos_y + d * ray->dir_y)) & 63;
		if (y < ray->draw_start)
			*(unsigned int *)(win->img->addr + (y * win->img->line_len + x * 4))
				= apply_fog(*(unsigned int *)(win->tex[5].addr
						+ (t[1] * win->tex[5].line_len + t[0] * 4)), d, p[1]);
		else
			*(unsigned int *)(win->img->addr + (y * win->img->line_len + x * 4))
				= apply_fog(*(unsigned int *)(win->tex[4].addr
						+ (t[1] * win->tex[4].line_len + t[0] * 4)), d, p[0]);
	}
}

void	get_pulses(const t_win *win, double p[6])
{
	p[0] = 1.0 + 0.2 * sin(win->pulse_time + 1.0);
	p[1] = 1.0 + 0.2 * sin(win->pulse_time + 3.0);
	p[2] = 1.0 + 0.2 * sin(win->pulse_time + 5.0);
	p[3] = 1.0 + 0.2 * sin(win->pulse_time + 4.0);
	p[4] = 1.0 + 0.2 * sin(win->pulse_time + 0.0);
	p[5] = 1.0 + 0.2 * sin(win->pulse_time + 2.0);
}

void	setup_ray_limits(const t_win *win, t_ray *ray)
{
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2 + win->player->pitch;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2 + win->player->pitch;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	apply_motion_blur(const t_win *win)
{
	int				i;
	unsigned int	*src;
	unsigned int	*acc;

	src = (unsigned int *)win->img->addr;
	acc = (unsigned int *)win->accum->addr;
	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		acc[i] = ((src[i] & 0xFEFEFE) >> 1) + ((src[i] & 0xFCFCFC) >> 2)
			+ ((acc[i] & 0xFCFCFC) >> 2);
		src[i] = acc[i];
		i++;
	}
}
