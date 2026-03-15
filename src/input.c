/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 17:10:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(const int keysym, t_win *win)
{
	if (keysym == XK_Escape)
		close_win(win);
	if (keysym < N_KEYS)
		win->keys[keysym] = 1;
	return (0);
}

int	key_release(const int keysym, t_win *win)
{
	if (keysym < N_KEYS)
		win->keys[keysym] = 0;
	return (0);
}

void update_dir(const t_win *win, t_player *p, double *dx, double *dy)
{
	if (win->keys[XK_w])
	{
		*dx += p->dir_x * p->speed;
		*dy += p->dir_y * p->speed;
	}
	if (win->keys[XK_s])
	{
		*dx -= p->dir_x * p->speed;
		*dy -= p->dir_y * p->speed;
	}
	if (win->keys[XK_a])
	{
		*dx += p->dir_y * p->speed;
		*dy -= p->dir_x * p->speed;
	}
	if (win->keys[XK_d])
	{
		*dx -= p->dir_y * p->speed;
		*dy += p->dir_x * p->speed;
	}
}

int	handle_input(const t_win *win)
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
		r = move_player((t_win *)win, dx, dy);
	if (win->keys[XK_Left])
		r += rotate_left(win->player);
	if (win->keys[XK_Right])
		r += rotate_right(win->player);
	return (r);
}
