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

int	move_player(const t_win *win, double dx, double dy)
{
	double	nx;
	double	ny;
	double	bx;
	double	by;

	nx = win->player->pos_x + dx;
	ny = win->player->pos_y + dy;
	bx = nx - win->player->radius;
	if (dx > 0)
		bx = nx + win->player->radius;
	if (win->map->grid[(int)(win->player->pos_y - win->player->radius)
		* win->map->width + (int)bx] != '1' &&
		win->map->grid[(int)(win->player->pos_y + win->player->radius)
		* win->map->width + (int)bx] != '1')
		win->player->pos_x = nx;
	by = ny - win->player->radius;
	if (dy > 0)
		by = ny + win->player->radius;
	if (win->map->grid[(int)by * win->map->width
		+ (int)(win->player->pos_x - win->player->radius)] != '1' &&
		win->map->grid[(int)by * win->map->width
		+ (int)(win->player->pos_x + win->player->radius)] != '1')
		win->player->pos_y = ny;
	return (1);
}

