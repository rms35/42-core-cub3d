/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:56:33 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 22:30:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	get_tex_x(const t_win *win, const t_ray *ray, int t[2])
{
	if (ray->side == 0)
		t[0] = (int)((win->player->pos_y + ray->perp_wall_dist * ray->dir_y)
				* 64.0) & 63;
	else
		t[0] = (int)((win->player->pos_x + ray->perp_wall_dist * ray->dir_x)
				* 64.0) & 63;
}

static void	draw_tex_col(const t_win *win, const t_ray *ray, int x, double p[2], double pos_z)
{
	int				y;
	double			pos;
	int				t[2];
	char			*dst;
	unsigned int	color;
	double			f;
	double			y_center;
	double			ratio;

	if (ray->line_height <= 0)
		return ;
	get_tex_x(win, ray, t);
	y_center = (double)HEIGHT / 2.0 + win->player->pitch;
	ratio = 64.0 / ray->line_height;
	pos = (ray->draw_start - y_center) * ratio + (0.5 - pos_z) * 64.0;
	if (pos < 0)
		pos = 0;
	y = ray->draw_start;
	dst = win->img->addr + (y * win->img->line_len + x * 4);
	f = 1.0 / (1.0 + ray->perp_wall_dist * ray->perp_wall_dist * 0.05);
	if (f > 1.0)
		f = 1.0;
	while (y <= ray->draw_end && y < HEIGHT)
	{
		t[1] = (int)pos & 63;
		pos += ratio;
		color = *(unsigned int *)(win->tex[(int)p[0]].addr + (t[1]
					* win->tex[(int)p[0]].line_len + t[0] * 4));
		*(unsigned int *)dst = apply_fog_factor(color, f, p[1]);
		dst += win->img->line_len;
		y++;
	}
}

static void	render_wall(const t_win *win, const t_ray *ray, int x, double p[6], double pos_z)
{
	double	param[2];

	if (ray->side == 0)
	{
		param[1] = p[2];
		param[0] = 2.0;
		if (ray->dir_x > 0)
			param[0] = 3.0;
		if (ray->dir_x <= 0)
			param[1] = p[3];
	}
	else
	{
		param[1] = p[0];
		param[0] = 0.0;
		if (ray->dir_y > 0)
			param[0] = 1.0;
		if (ray->dir_y <= 0)
			param[1] = p[1];
	}
	draw_tex_col(win, ray, x, param, pos_z);
}

void	render_frame(const t_win *win)
{
	t_ray	ray;
	int		x;
	double	p[6];
	double	ep[2];

	get_pulses(win, p);
	ep[0] = p[4];
	ep[1] = p[5];
	x = -1;
	while (++x < WIDTH)
	{
		init_ray(win, &ray, x);
		perform_dda(win, &ray);
		setup_ray_limits(win, &ray, win->player->pos_z);
		render_env(win, &ray, x, ep, win->player->pos_z);
		render_wall(win, &ray, x, p, win->player->pos_z);
	}
	apply_motion_blur(win);
	render_hud(win);
}
