/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 22:30:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	mouse_move(int x, int y, t_win *win)
{
	win->mouse_x = x;
	win->mouse_y = y;
	return (0);
}

static void	process_mouse(t_win *win)
{
	int	dx;
	int	dy;

	dx = win->mouse_x - WIDTH / 2;
	dy = win->mouse_y - HEIGHT / 2;
	if (dx != 0)
		rotate_player(win->player, dx * 0.0005);
	win->player->pitch -= dy * 2;
	if (win->player->pitch > 400)
		win->player->pitch = 400;
	if (win->player->pitch < -400)
		win->player->pitch = -400;
	mlx_mouse_move(win->mlxptr, win->winptr, WIDTH / 2, HEIGHT / 2);
	win->mouse_x = WIDTH / 2;
	win->mouse_y = HEIGHT / 2;
}

static void	get_move_vec(t_win *win, double d[2], double s)
{
	if (win->keys[XK_w] || win->keys[XK_W])
	{
		d[0] += win->player->dir_x * s;
		d[1] += win->player->dir_y * s;
	}
	if (win->keys[XK_s] || win->keys[XK_S])
	{
		d[0] -= win->player->dir_x * win->player->speed;
		d[1] -= win->player->dir_y * win->player->speed;
	}
	if (win->keys[XK_a] || win->keys[XK_A])
	{
		d[0] += win->player->dir_y * win->player->speed;
		d[1] -= win->player->dir_x * win->player->speed;
	}
	if (win->keys[XK_d] || win->keys[XK_D])
	{
		d[0] -= win->player->dir_y * win->player->speed;
		d[1] += win->player->dir_x * win->player->speed;
	}
}

static void	toggle_door(t_win *win, int x, int y)
{
	if (x < 0 || x >= win->map->width || y < 0 || y >= win->map->height)
		return ;
	if (win->map->grid[y * win->map->width + x] != 'D')
		return ;
	if (win->map->door_target[y * win->map->width + x] > 0.5)
		win->map->door_target[y * win->map->width + x] = 0.0;
	else
		win->map->door_target[y * win->map->width + x] = 0.95;
}

static void	interact_door(t_win *win)
{
	int		mx;
	int		my;

	mx = (int)(win->player->pos_x + win->player->dir_x * 0.8);
	my = (int)(win->player->pos_y + win->player->dir_y * 0.8);
	if (win->map->grid[my * win->map->width + mx] == 'D')
	{
		toggle_door(win, mx, my);
		toggle_door(win, mx + 1, my);
		toggle_door(win, mx - 1, my);
		toggle_door(win, mx, my + 1);
		toggle_door(win, mx, my - 1);
	}
}

int	handle_input(t_win *win)
{
	double	d[2];
	double	s;
	int		moved;

	process_mouse(win);
	if (win->keys[XK_e] || win->keys[XK_E])
	{
		interact_door(win);
		win->keys[XK_e] = 0;
		win->keys[XK_E] = 0;
	}
	d[0] = 0;
	d[1] = 0;
	s = win->player->speed;
	if (win->keys[XK_Shift_L] || win->keys[XK_Shift_R])
		s *= 2.5;
	get_move_vec(win, d, s);
	moved = move_player(win, d[0], d[1]);
	if (moved)
	{
		win->player->walk_t += 0.15 * (s / win->player->speed);
		if (win->player->walk_t > M_PI * 2.0)
			win->player->walk_t -= M_PI * 2.0;
	}
	else
		win->player->walk_t = 0;
	return (moved);
}
