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

int	handle_input(t_win *win)
{
	int	r;

	r = 0;
	if (win->keys[XK_w])
		r |= move_up(win->map->grid, win->map->width, win->player);
	if (win->keys[XK_s])
		r |= move_down(win->map->grid, win->map->width, win->player);
	if (win->keys[XK_a])
		r |= move_left(win->map->grid, win->map->width, win->player);
	if (win->keys[XK_d])
		r |= move_right(win->map->grid, win->map->width, win->player);
	if (win->keys[XK_Left])
		r |= rotate_left(win->player);
	if (win->keys[XK_Right])
		r |= rotate_right(win->player);
	return (r);
}
