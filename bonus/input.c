/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/20 13:40:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	key_press(int keysym, t_win *win)
{
	if (keysym == XK_Escape)
		close_win(win);
	if (keysym < N_KEYS)
		win->keys[keysym] = 1;
	return (0);
}

int	key_release(int keysym, t_win *win)
{
	if (keysym < N_KEYS)
		win->keys[keysym] = 0;
	return (0);
}

static void	update_dir(const t_win *win, t_player *p, double *dx, double *dy)
{
	double move_speed;

	move_speed= win->player->speed * win->delta_time;
	if (win->keys[XK_w])
	{
		move_speed= win->player->fwd_speed * win->delta_time;
		*dx += p->dir_x * move_speed;
		*dy += p->dir_y * move_speed;
	}
	if (win->keys[XK_s])
	{
		*dx -= p->dir_x * move_speed;
		*dy -= p->dir_y * move_speed;
	}
	if (win->keys[XK_a])
	{
		*dx += p->dir_y * move_speed;
		*dy -= p->dir_x * move_speed;
	}
	if (win->keys[XK_d])
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
	if (win->keys[XK_Shift_L])
		win->player->fwd_speed = 3 * P1_SPEED;
	else
		win->player->fwd_speed = P1_SPEED;
	return (r);
}
