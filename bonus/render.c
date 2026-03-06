/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:56:33 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 19:15:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	draw_tex_line(const t_win *win, const t_ray *ray, int x, double p[2])
{
	int		y;
	double	step;
	double	pos;
	int		t[2];
	char	*dst;

	if (ray->side == 0)
		t[0] = (int)((win->player->pos_y + ray->perp_wall_dist * ray->dir_y)
				* 64.0) & 63;
	else
		t[0] = (int)((win->player->pos_x + ray->perp_wall_dist * ray->dir_x)
				* 64.0) & 63;
	step = 1.0 * 64 / ray->line_height;
	pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2) * step;
	y = ray->draw_start;
	dst = win->img->addr + (y * win->img->line_len + x * 4);
	while (y <= ray->draw_end)
	{
		t[1] = (int)pos & 63;
		pos += step;
		*(unsigned int *)dst = apply_fog(*(unsigned int *)(win->tex[(int)p[0]]
					.addr + (t[1] * win->tex[(int)p[0]].line_len + t[0] * 4)),
				ray->perp_wall_dist, p[1]);
		dst += win->img->line_len;
		y++;
	}
}

static void	render_wall(const t_win *win, const t_ray *ray, int x, double p[6])
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
	draw_tex_line(win, ray, x, param);
}

static void	get_pulses(const t_win *win, double p[6])
{
	p[0] = 1.0 + 0.2 * sin(win->pulse_time + 1.0);
	p[1] = 1.0 + 0.2 * sin(win->pulse_time + 3.0);
	p[2] = 1.0 + 0.2 * sin(win->pulse_time + 5.0);
	p[3] = 1.0 + 0.2 * sin(win->pulse_time + 4.0);
	p[4] = 1.0 + 0.2 * sin(win->pulse_time + 0.0);
	p[5] = 1.0 + 0.2 * sin(win->pulse_time + 2.0);
}

void	render_frame(const t_win *win)
{
	t_ray	ray;
	int		x;
	double	p[6];
	double	env_p[2];

	get_pulses(win, p);
	env_p[0] = p[4];
	env_p[1] = p[5];
	x = -1;
	while (++x < WIDTH)
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
		render_env(win, &ray, x, env_p);
		render_wall(win, &ray, x, p);
	}
}
