/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 18:50:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static int	can_move(t_map *map, double x, double y)
{
	int	mx;
	int	my;

	mx = (int)x;
	my = (int)y;
	if (map->grid[my * map->width + mx] == '1')
		return (0);
	if (map->grid[my * map->width + mx] == 'D'
		&& map->door_state[my * map->width + mx] < 0.5)
		return (0);
	return (1);
}

static void	apply_move(t_win *win, t_player *p, double move[2])
{
	double	nx;
	double	ny;
	double	bx;
	double	by;

	nx = p->pos_x + move[0];
	ny = p->pos_y + move[1];
	if (move[0] > 0)
		bx = nx + BUFFER;
	else
		bx = nx - BUFFER;
	if (move[1] > 0)
		by = ny + BUFFER;
	else
		by = ny - BUFFER;
	if (can_move(win->map, bx, p->pos_y))
		p->pos_x = nx;
	if (can_move(win->map, p->pos_x, by))
		p->pos_y = ny;
}

int	move_player(t_win *win, double dx, double dy)
{
	double	move[2];

	if (dx == 0 && dy == 0)
		return (0);
	move[0] = dx;
	move[1] = dy;
	apply_move(win, win->player, move);
	return (1);
}
