/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 18:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/07 18:10:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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

static void	render_sky(const t_win *win, int x, int y, double dir_glow, double angle)
{
	int		t[2];
	unsigned int sky_col;
	double h_glow;
	double glow;
	int r, g, b;

	(void)win;
	t[0] = (int)(win->sky_tex.width * (angle + M_PI) / (2.0 * M_PI));
	t[0] = (t[0] % win->sky_tex.width + win->sky_tex.width) % win->sky_tex.width;
	t[1] = (y - win->player->pitch + HEIGHT) * win->sky_tex.height / (HEIGHT * 2);
	if (t[1] < 0) t[1] = 0;
	if (t[1] >= win->sky_tex.height) t[1] = win->sky_tex.height - 1;
	sky_col = *(unsigned int *)(win->sky_tex.addr + (t[1] * win->sky_tex.line_len + t[0] * 4));
	h_glow = (double)t[1] / win->sky_tex.height;
	if (h_glow < 0) h_glow = 0;
	glow = dir_glow * (h_glow * h_glow) * 0.9;
	r = (int)((sky_col >> 16 & 0xFF) * (1.0 - glow) + 0x00 * glow);
	g = (int)((sky_col >> 8 & 0xFF) * (1.0 - glow) + 0xFF * glow);
	b = (int)((sky_col & 0xFF) * (1.0 - glow) + 0xBB * glow);
	*(unsigned int *)(win->img->addr + (y * win->img->line_len + x * 4)) = (r << 16 | g << 8 | b);
}

unsigned int	apply_fog_factor(unsigned int color, double f, double p)
{
	int		rgb[3];

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

void	render_env(const t_win *win, const t_ray *ray, int x, double p[2], double pos_z)
{
	int		y;
	double	d;
	int		t[2];
	char	tile;
	double	wx, wy, dir_glow, denom, h_factor, angle;
	int		e_start, e_end;

	angle = atan2(ray->dir_y, ray->dir_x);
	dir_glow = cos(angle);
	if (dir_glow < 0) dir_glow = 0;
	dir_glow = dir_glow * dir_glow;
	
	int l_h = (int)(HEIGHT / ray->perp_wall_dist);
	e_start = (int)((HEIGHT / 2.0 + win->player->pitch) - (0.5 - pos_z) * l_h);
	e_end = (int)((HEIGHT / 2.0 + win->player->pitch) + (0.5 + pos_z) * l_h);
	if (e_start < 0) e_start = 0;
	if (e_end >= HEIGHT) e_end = HEIGHT - 1;

	y = -1;
	while (++y < HEIGHT)
	{
		if (y >= e_start && y <= e_end)
			continue ;
		denom = fabs(HEIGHT / 2.0 - (y - win->player->pitch));
		if (denom < 0.1) denom = 0.1;
		h_factor = 0.5 + pos_z;
		if (y < e_start)
			h_factor = 0.5 - pos_z;
		d = h_factor * HEIGHT / denom;
		wx = win->player->pos_x + d * ray->dir_x;
		wy = win->player->pos_y + d * ray->dir_y;
		tile = '0';
		if (wx >= 0 && wx < win->map->width && wy >= 0 && wy < win->map->height)
			tile = win->map->grid[(int)wy * win->map->width + (int)wx];
		if (y < e_start)
		{
			if (tile == '2' || tile == 'D' || !win->sky_tex.img)
			{
				t[0] = (int)(64 * wx) & 63;
				t[1] = (int)(64 * wy) & 63;
				if (tile == '2')
					*(unsigned int *)(win->img->addr + (y * win->img->line_len + x * 4)) = apply_fog_factor(*(unsigned int *)(win->tex[5].addr + (t[1] * win->tex[5].line_len + t[0] * 4)), (1.0 / (1.0 + d * d * 0.05)), p[1]);
				else if (tile == 'D')
					*(unsigned int *)(win->img->addr + (y * win->img->line_len + x * 4)) = apply_fog_factor(*(unsigned int *)(win->tex[8].addr + (t[1] * win->tex[8].line_len + t[0] * 4)), (1.0 / (1.0 + d * d * 0.05)), p[1]);
				else
					*(unsigned int *)(win->img->addr + (y * win->img->line_len + x * 4)) = win->map->ceil_color;
			}
			else
				render_sky(win, x, y, dir_glow, angle);
		}
		else
		{
			t[0] = (int)(64 * wx) & 63;
			t[1] = (int)(64 * wy) & 63;
			*(unsigned int *)(win->img->addr + (y * win->img->line_len + x * 4)) = apply_fog_factor(*(unsigned int *)(win->tex[4].addr + (t[1] * win->tex[4].line_len + t[0] * 4)), 1.0 / (1.0 + d * d * 0.05), p[0]);
		}
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

void	setup_ray_limits(const t_win *win, t_ray *ray, double pos_z)
{
	double	y_center;

	(void)win;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	y_center = (double)HEIGHT / 2.0 + win->player->pitch;
	ray->draw_start = (int)(y_center - (0.5 - pos_z) * ray->line_height);
	ray->draw_end = (int)(y_center + (0.5 + pos_z) * ray->line_height);
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

void	apply_motion_blur(const t_win *win)
{
	int				y;
	unsigned int	*src;
	unsigned int	*acc;
	int				row_add;
	int				x;

	y = 0;
	row_add = win->img->line_len / 4;
	src = (unsigned int *)win->img->addr;
	acc = (unsigned int *)win->accum->addr;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			acc[x] = ((src[x] & 0xFEFEFE) >> 1) + ((src[x] & 0xFCFCFC) >> 2)
				+ ((acc[x] & 0xFCFCFC) >> 2);
			src[x] = acc[x];
			x++;
		}
		src += row_add;
		acc += row_add;
		y++;
	}
}
