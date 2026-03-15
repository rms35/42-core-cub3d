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

#include "../includes/cub3d.h"

int	move_up(const char *grid, const int width, t_player *player)
{
	double	nx;
	double	ny;
	double	bx;
	double	by;

	nx = player->pos_x + player->dir_x * player->speed;
	ny = player->pos_y + player->dir_y * player->speed;
	if (player->dir_x > 0)
		bx = nx + player->radius;
	else
		bx = nx - player->radius;
	if (player->dir_y > 0)
		by = ny + player->radius;
	else
		by = ny - player->radius;
	if (grid[(int)player->pos_y * width + (int)bx] != '1')
		player->pos_x = nx;
	if (grid[(int)by * width + (int)player->pos_x] != '1')
		player->pos_y = ny;
	return (1);
}

int	move_down(const char *grid, const int width, t_player *player)
{
	double	nx;
	double	ny;
	double	bx;
	double	by;

	nx = player->pos_x - player->dir_x * player->speed;
	ny = player->pos_y - player->dir_y * player->speed;
	if (player->dir_x > 0)
		bx = nx - player->radius;
	else
		bx = nx + player->radius;
	if (player->dir_y > 0)
		by = ny - player->radius;
	else
		by = ny + player->radius;
	if (grid[(int)player->pos_y * width + (int)bx] != '1')
		player->pos_x = nx;
	if (grid[(int)by * width + (int)player->pos_x] != '1')
		player->pos_y = ny;
	return (1);
}

int	move_left(const char *grid, const int width, t_player *player)
{
	double	nx;
	double	ny;
	double	bx;
	double	by;

	nx = player->pos_x + player->dir_y * player->speed;
	ny = player->pos_y - player->dir_x * player->speed;
	if (player->dir_y > 0)
		bx = nx + player->radius;
	else
		bx = nx - player->radius;
	if (player->dir_x > 0)
		by = ny - player->radius;
	else
		by = ny + player->radius;
	if (grid[(int)player->pos_y * width + (int)bx] != '1')
		player->pos_x = nx;
	if (grid[(int)by * width + (int)player->pos_x] != '1')
		player->pos_y = ny;
	return (1);
}

int	move_right(const char *grid, const int width, t_player *player)
{
	double	nx;
	double	ny;
	double	bx;
	double	by;

	nx = player->pos_x - player->dir_y * player->speed;
	ny = player->pos_y + player->dir_x * player->speed;
	if (player->dir_y > 0)
		bx = nx - player->radius;
	else
		bx = nx + player->radius;
	if (player->dir_x > 0)
		by = ny + player->radius;
	else
		by = ny - player->radius;
	if (grid[(int)player->pos_y * width + (int)bx] != '1')
		player->pos_x = nx;
	if (grid[(int)by * width + (int)player->pos_x] != '1')
		player->pos_y = ny;
	return (1);
}


