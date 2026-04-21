/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 12:00:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	check_fire_collision_x(t_win *win, double next_x, double next_y,
	int y)
{
	double	dist_x;
	double	dist_y;

	dist_x = next_x - ((int)next_x + 0.5);
	dist_y = next_y - (y + 0.5);
	if (win->map->grid[y * win->map->width + (int)next_x] == 'F'
		&& sqrt(dist_x * dist_x + dist_y * dist_y)
		< win->player->radius + F_RADIUS)
		return (1);
	return (0);
}

static void	move_x(t_win *win, double next_x, double prev_x, t_sprite *door)
{
	int		y_coords[2];
	int		x_int;

	y_coords[0] = (int)(win->player->pos_y - win->player->radius);
	y_coords[1] = (int)(win->player->pos_y + win->player->radius);
	x_int = (int)prev_x;
	if (x_int < 0 || x_int >= (int)win->map->width || y_coords[0] < 0
		|| y_coords[0] >= (int)win->map->height || y_coords[1] < 0
		|| y_coords[1] >= (int)win->map->height)
		return ;
	if (ft_strchr(WALLS, win->map->grid[y_coords[0] * win->map->width + x_int])
		|| ft_strchr(WALLS, win->map->grid[y_coords[1] * win->map->width
				+ x_int]) || (door && !door->open))
		return ;
	if (check_fire_collision_x(win, next_x, win->player->pos_y, y_coords[0])
		|| check_fire_collision_x(win, next_x, win->player->pos_y, y_coords[1]))
		return ;
	win->player->pos_x = next_x;
}

static int	check_fire_collision_y(t_win *win, double next_x, double next_y,
	int x)
{
	double	dist_x;
	double	dist_y;

	dist_x = next_x - (x + 0.5);
	dist_y = next_y - ((int)next_y + 0.5);
	if (win->map->grid[(int)next_y * win->map->width + x] == 'F'
		&& sqrt(dist_x * dist_x + dist_y * dist_y)
		< win->player->radius + F_RADIUS)
		return (1);
	return (0);
}

static void	move_y(t_win *win, double next_y, double prev_y, t_sprite *door)
{
	int		x_coords[2];
	int		y_int;

	x_coords[0] = (int)(win->player->pos_x - win->player->radius);
	x_coords[1] = (int)(win->player->pos_x + win->player->radius);
	y_int = (int)prev_y;
	if (y_int < 0 || y_int >= (int)win->map->height || x_coords[0] < 0
		|| x_coords[0] >= (int)win->map->width || x_coords[1] < 0
		|| x_coords[1] >= (int)win->map->width)
		return ;
	if (ft_strchr(WALLS, win->map->grid[y_int * win->map->width
				+ x_coords[0]]) || ft_strchr(WALLS, win->map->grid[y_int
				* win->map->width + x_coords[1]]) || (door && !door->open))
		return ;
	if (check_fire_collision_y(win, win->player->pos_x, next_y, x_coords[0])
		|| check_fire_collision_y(win, win->player->pos_x, next_y, x_coords[1]))
		return ;
	win->player->pos_y = next_y;
}

int	move_player(t_win *win, double dx, double dy)
{
	double		next_x;
	double		next_y;
	double		prev_x;
	double		prev_y;
	t_sprite	*door;

	next_x = win->player->pos_x + dx;
	next_y = win->player->pos_y + dy;
	door = get_door(win->sprites, win->n_sprites, (int)floor(next_x),
			(int)floor(next_y));
	if (dx > 0)
		prev_x = next_x + win->player->radius;
	else
		prev_x = next_x - win->player->radius;
	move_x(win, next_x, prev_x, door);
	if (dy > 0)
		prev_y = next_y + win->player->radius;
	else
		prev_y = next_y - win->player->radius;
	move_y(win, next_y, prev_y, door);
	return (1);
}
