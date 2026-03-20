/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 18:55:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	move_x(t_win *win, const double next_x, const double prev_x)
{
	int		y[2];
	int		x;
	double	d[2];

	y[0] = (int)(win->player->pos_y - win->player->radius);
	y[1] = (int)(win->player->pos_y + win->player->radius);
	x = (int)prev_x;
	if (win->map->grid[y[0] * win->map->width + x] == '1' ||
		win->map->grid[y[1] * win->map->width + x] == '1')
		return ;
	d[0] = next_x - (x + 0.5);
	d[1] = win->player->pos_y - (y[0] + 0.5);
	if (win->map->grid[y[0] * win->map->width + x] == 'F'
		&& sqrt(d[0] * d[0] + d[1] * d[1]) < win->player->radius + F_RADIUS)
		return ;
	d[1] = win->player->pos_y - (y[1] + 0.5);
	if (win->map->grid[y[1] * win->map->width + x] == 'F'
		&& sqrt(d[0] * d[0] + d[1] * d[1]) < win->player->radius + F_RADIUS)
		return ;
	win->player->pos_x = next_x;
}

static void	move_y(t_win *win, const double next_y, const double prev_y)
{
	int		x[2];
	int		y;
	double	d[2];

	x[0] = (int)(win->player->pos_x - win->player->radius);
	x[1] = (int)(win->player->pos_x + win->player->radius);
	y = (int)prev_y;
	if (win->map->grid[y * win->map->width + x[0]] == '1' ||
		win->map->grid[y * win->map->width + x[1]] == '1')
		return ;
	d[0] = win->player->pos_x - (x[0] + 0.5);
	d[1] = next_y - (y + 0.5);
	if (win->map->grid[y * win->map->width + x[0]] == 'F'
		&& sqrt(d[0] * d[0] + d[1] * d[1]) < win->player->radius + F_RADIUS)
		return ;
	d[0] = win->player->pos_x - (x[1] + 0.5);
	if (win->map->grid[y * win->map->width + x[1]] == 'F'
		&& sqrt(d[0] * d[0] + d[1] * d[1]) < win->player->radius + F_RADIUS)
		return ;
	win->player->pos_y = next_y;
}

int	move_player(t_win *win, const double dx, const double dy)
{
	double	next_x;
	double	next_y;
	double	prev_x;
	double	prev_y;

	next_x = win->player->pos_x + dx;
	next_y = win->player->pos_y + dy;
	if (dx > 0)
		prev_x = next_x + win->player->radius;
	else
		prev_x = next_x - win->player->radius;
	move_x(win, next_x, prev_x);
	if (dy > 0)
		prev_y = next_y + win->player->radius;
	else
		prev_y = next_y - win->player->radius;
	move_y(win, next_y, prev_y);
	return (1);
}

