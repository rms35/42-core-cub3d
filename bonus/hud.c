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

#include "../includes/cub3d.h"

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

static void	draw_minimap(const t_win *win)
{
	int	x;
	int	y;
	int	s;
	int	c;

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
			draw_rect(win, (int [2]){x * s + 20, x * s + s + 20},
				(int [2]){y * s + 20, y * s + s + 20}, c);
		}
	}
	draw_rect(win, (int [2]){win->player->pos_x * s + 18,
		win->player->pos_x * s + 22},
		(int [2]){win->player->pos_y * s + 18,
		win->player->pos_y * s + 22}, 0xff00ff);
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
