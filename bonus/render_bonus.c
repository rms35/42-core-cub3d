/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 18:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 19:15:00 by rafael           ###   ########.fr       */
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
	char	*c_ptr;
	char	*f_ptr;

	y = 0;
	c_ptr = win->img->addr + (x * 4);
	f_ptr = win->img->addr + ((HEIGHT - 1) * win->img->line_len + x * 4);
	while (y < ray->draw_start && (HEIGHT - 1 - y) > ray->draw_end)
	{
		d = HEIGHT / (double)(HEIGHT - 2 * y);
		t[0] = (int)(64 * (win->player->pos_x + d * ray->dir_x)) & 63;
		t[1] = (int)(64 * (win->player->pos_y + d * ray->dir_y)) & 63;
		*(unsigned int *)c_ptr = apply_fog(*(unsigned int *)(win->tex[5].addr
					+ (t[1] * win->tex[5].line_len + t[0] * 4)), d, p[1]);
		*(unsigned int *)f_ptr = apply_fog(*(unsigned int *)(win->tex[4].addr
					+ (t[1] * win->tex[4].line_len + t[0] * 4)), d, p[0]);
		c_ptr += win->img->line_len;
		f_ptr -= win->img->line_len;
		y++;
	}
}
