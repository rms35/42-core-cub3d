/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/17 20:52:10 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	key_press(const int keysym, t_win *win)
{
	if (keysym == ESC_KEY)
		close_win(win);
	if (keysym == W_KEY)
		win->keys[W] = 1;
	else if (keysym == A_KEY)
		win->keys[A] = 1;
	else if (keysym == S_KEY)
		win->keys[S] = 1;
	else if (keysym == D_KEY)
		win->keys[D] = 1;
	else if (keysym == LARRW_KEY)
		win->keys[LA] = 1;
	else if (keysym == RARRW_KEY)
		win->keys[RA] = 1;
	return (0);
}

int	key_release(const int keysym, t_win *win)
{
	if (keysym == W_KEY)
		win->keys[W] = 0;
	else if (keysym == A_KEY)
		win->keys[A] = 0;
	else if (keysym == S_KEY)
		win->keys[S] = 0;
	else if (keysym == D_KEY)
		win->keys[D] = 0;
	else if (keysym == LARRW_KEY)
		win->keys[LA] = 0;
	else if (keysym == RARRW_KEY)
		win->keys[RA] = 0;
	return (0);
}

void update_dir(const t_win *win, const t_player *p, double *dx, double *dy)
{
	if (win->keys[W])
	{
		*dx += p->dir_x * p->speed;
		*dy += p->dir_y * p->speed;
	}
	if (win->keys[S])
	{
		*dx -= p->dir_x * p->speed;
		*dy -= p->dir_y * p->speed;
	}
	if (win->keys[A])
	{
		*dx += p->dir_y * p->speed;
		*dy -= p->dir_x * p->speed;
	}
	if (win->keys[D])
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
	if (win->keys[LA])
		r += rotate_left(win->player);
	if (win->keys[RA])
		r += rotate_right(win->player);
	return (r);
}
