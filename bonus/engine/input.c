/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 12:00:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	key_press(int keysym, void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (keysym == KEY_ESC)
		close_win(win);
	if (keysym < N_KEYS)
		win->keys[keysym] = 1;
	return (0);
}

int	key_release(int keysym, void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (keysym < N_KEYS)
		win->keys[keysym] = 0;
	return (0);
}

static void	update_dir(t_win *win, t_player *p, double *dx, double *dy)
{
	double	move_speed;

	move_speed = win->player->speed * win->delta_time;
	if (win->keys[KEY_W])
	{
		move_speed = win->player->fwd_speed * win->delta_time;
		*dx += p->dir_x * move_speed;
		*dy += p->dir_y * move_speed;
	}
	if (win->keys[KEY_S])
	{
		*dx -= p->dir_x * move_speed;
		*dy -= p->dir_y * move_speed;
	}
	if (win->keys[KEY_A])
	{
		*dx += p->dir_y * move_speed;
		*dy -= p->dir_x * move_speed;
	}
	if (win->keys[KEY_D])
	{
		*dx -= p->dir_y * move_speed;
		*dy += p->dir_x * move_speed;
	}
}

int	handle_input(t_win *win)
{
	t_player	*p;
	double		dx;
	double		dy;
	int			r;

	r = 0;
	p = win->player;
	dx = 0;
	dy = 0;
	update_dir(win, p, &dx, &dy);
	if (dx != 0 || dy != 0)
		r = move_player(win, dx, dy);
	if (win->keys[KEY_SHIFT])
		win->player->fwd_speed = 2.5 * P1_SPEED;
	else
		win->player->fwd_speed = P1_SPEED;
	if (win->keys[KEY_E])
		open_door(win);
	return (r);
}
