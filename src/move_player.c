/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/01 12:00:00 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	move_up(char *grid, const int width, t_player *player)
{
	double	nx;
	double	ny;

	nx = player->pos_x - player->dir_x * player->speed;
	ny = player->pos_y - player->dir_y * player->speed;
	if (grid[(int)player->pos_y * width + (int)nx] != '1')
		player->pos_x = nx;
	if (grid[(int)ny * width + (int)player->pos_x] != '1')
		player->pos_y = ny;
	grid[player->grid_pos] = '0';
	player->grid_pos = (int)player->pos_y * width + (int)player->pos_x;
	grid[player->grid_pos] = 'P';
	return (1);
}

int	move_down(char *grid, const int width, t_player *player)
{
	double	nx;
	double	ny;

	nx = player->pos_x + player->dir_x * player->speed;
	ny = player->pos_y + player->dir_y * player->speed;
	if (grid[(int)player->pos_y * width + (int)nx] != '1')
		player->pos_x = nx;
	if (grid[(int)ny * width + (int)player->pos_x] != '1')
		player->pos_y = ny;
	grid[player->grid_pos] = '0';
	player->grid_pos = (int)player->pos_y * width + (int)player->pos_x;
	grid[player->grid_pos] = 'P';
	return (1);
}

int	move_left(char *grid, const int width, t_player *player)
{
	double	nx;
	double	ny;

	nx = player->pos_x - player->dir_y * player->speed;
	ny = player->pos_y + player->dir_x * player->speed;
	if (grid[(int)player->pos_y * width + (int)nx] != '1')
		player->pos_x = nx;
	if (grid[(int)ny * width + (int)player->pos_x] != '1')
		player->pos_y = ny;
	grid[player->grid_pos] = '0';
	player->grid_pos = (int)player->pos_y * width + (int)player->pos_x;
	grid[player->grid_pos] = 'P';
	return (1);
}

int	move_right(char *grid, const int width, t_player *player)
{
	double	nx;
	double	ny;

	nx = player->pos_x + player->dir_y * player->speed;
	ny = player->pos_y - player->dir_x * player->speed;
	if (grid[(int)player->pos_y * width + (int)nx] != '1')
		player->pos_x = nx;
	if (grid[(int)ny * width + (int)player->pos_x] != '1')
		player->pos_y = ny;
	grid[player->grid_pos] = '0';
	player->grid_pos = (int)player->pos_y * width + (int)player->pos_x;
	grid[player->grid_pos] = 'P';
	return (1);
}
