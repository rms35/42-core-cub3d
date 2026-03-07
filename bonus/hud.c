/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 19:20:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 19:20:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	draw_pixel(const t_win *win, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = win->img->addr + (y * win->img->line_len + x * 4);
	*(unsigned int *)dst = color;
}

static void	draw_rect(const t_win *win, int x[2], int y[2], int color)
{
	int	i;
	int	j;

	i = y[0];
	while (i < y[1])
	{
		j = x[0];
		while (j < x[1])
		{
			draw_pixel(win, j, i, color);
			j++;
		}
		i++;
	}
}

static void	draw_line(const t_win *win, double x[2], double y[2], int color)
{
	double	dx;
	double	dy;
	double	step;
	double	i;
	double	curr[2];

	dx = x[1] - x[0];
	dy = y[1] - y[0];
	if (fabs(dx) >= fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	dx /= step;
	dy /= step;
	curr[0] = x[0];
	curr[1] = y[0];
	i = 0;
	while (i <= step)
	{
		draw_pixel(win, (int)curr[0], (int)curr[1], color);
		curr[0] += dx;
		curr[1] += dy;
		i++;
	}
}

static void	draw_minimap(const t_win *win)
{
	int		x;
	int		y;
	int		s;
	int		c;
	double	p[2];

	s = 10;
	y = -1;
	while (++y < win->map->height)
	{
		x = -1;
		while (++x < win->map->width)
		{
			c = 0x1a1b26;
			if (win->map->grid[y * win->map->width + x] == '1')
				c = 0x7aa2f7;
			else if (win->map->grid[y * win->map->width + x] == 'D')
				c = 0xff9e64;
			draw_rect(win, (int [2]){x * s + 20, x * s + s + 20},
				(int [2]){y * s + 20, y * s + s + 20}, c);
		}
	}
	p[0] = win->player->pos_x * s + 20;
	p[1] = win->player->pos_y * s + 20;
	double tip[2] = {p[0] + win->player->dir_x * 10, p[1] + win->player->dir_y * 10};
	double left[2] = {p[0] - win->player->dir_x * 4 + win->player->dir_y * 4,
					  p[1] - win->player->dir_y * 4 - win->player->dir_x * 4};
	double right[2] = {p[0] - win->player->dir_x * 4 - win->player->dir_y * 4,
					   p[1] - win->player->dir_y * 4 + win->player->dir_x * 4};
	draw_line(win, (double [2]){tip[0], left[0]}, (double [2]){tip[1], left[1]}, 0xff00ff);
	draw_line(win, (double [2]){tip[0], right[0]}, (double [2]){tip[1], right[1]}, 0xff00ff);
	draw_line(win, (double [2]){left[0], right[0]}, (double [2]){left[1], right[1]}, 0xff00ff);
}

static void	draw_scanlines(const t_win *win)
{
	int		x;
	int		y;
	char	*dst;

	y = 0;
	while (y < HEIGHT)
	{
		if (y % 3 == 0)
		{
			x = 0;
			dst = win->img->addr + (y * win->img->line_len);
			while (x < WIDTH)
			{
				*(unsigned int *)dst = (*(unsigned int *)dst >> 1) & 0x7F7F7F;
				dst += 4;
				x++;
			}
		}
		y++;
	}
}

void	render_hud(const t_win *win)
{
	int	cx;
	int	cy;

	draw_minimap(win);
	draw_scanlines(win);
	cx = WIDTH / 2;
	cy = HEIGHT / 2;
	draw_rect(win, (int [2]){cx - 10, cx + 10}, (int [2]){cy - 1, cy + 1},
		0x00ffff);
	draw_rect(win, (int [2]){cx - 1, cx + 1}, (int [2]){cy - 10, cy + 10},
		0x00ffff);
}
