/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 18:55:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_press(const int keysym, t_win *win)
{
	if (keysym == XK_Escape)
		close_win(win, EXIT_SUCCESS);
	if (keysym < 65536)
		win->keys[keysym] = 1;
	return (0);
}

int	key_release(const int keysym, t_win *win)
{
	if (keysym < 65536)
		win->keys[keysym] = 0;
	return (0);
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
		d[0] -= win->player->dir_x * s;
		d[1] -= win->player->dir_y * s;
	}
	if (win->keys[XK_a] || win->keys[XK_A])
	{
		d[0] += win->player->dir_y * s;
		d[1] -= win->player->dir_x * s;
	}
	if (win->keys[XK_d] || win->keys[XK_D])
	{
		d[0] -= win->player->dir_y * s;
		d[1] += win->player->dir_x * s;
	}
}

int	handle_input(t_win *win)
{
	int		r;
	double	d[2];
	double	s;

	r = 0;
	d[0] = 0;
	d[1] = 0;
	s = win->player->speed;
	if (win->keys[XK_Shift_L] || win->keys[XK_Shift_R])
		s *= 2.5;
	get_move_vec(win, d, s);
	r |= move_player(win, d[0], d[1]);
	if (win->keys[XK_Left])
		r |= rotate_left(win->player);
	if (win->keys[XK_Right])
		r |= rotate_right(win->player);
	return (r);
}
