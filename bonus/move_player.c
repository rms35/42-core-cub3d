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

#include "../includes/cub3d.h"

static void	apply_move(char *grid, int width, t_player *p, double move[2])
{
	double	bx;
	double	by;

	if (move[0] > 0)
		bx = p->pos_x + move[0] + BUFFER;
	else
		bx = p->pos_x + move[0] - BUFFER;
	if (move[1] > 0)
		by = p->pos_y + move[1] + BUFFER;
	else
		by = p->pos_y + move[1] - BUFFER;
	if (grid[(int)p->pos_y * width + (int)bx] != '1')
		p->pos_x += move[0];
	if (grid[(int)by * width + (int)p->pos_x] != '1')
		p->pos_y += move[1];
	p->grid_pos = (int)p->pos_y * width + (int)p->pos_x;
}

int	move_player(t_win *win, double dx, double dy)
{
	double	move[2];

	if (dx == 0 && dy == 0)
		return (0);
	move[0] = dx;
	move[1] = dy;
	apply_move(win->map->grid, win->map->width, win->player, move);
	return (1);
}
