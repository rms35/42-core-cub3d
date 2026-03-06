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

int	handle_input(t_win *win)
{
	int		r;
	double	old_speed;

	r = 0;
	old_speed = win->player->speed;
	if (win->keys[XK_Shift_L] || win->keys[XK_Shift_R])
		win->player->speed *= 2.5;
	if (win->keys[XK_w] || win->keys[XK_W])
		r |= move_up(win->map->grid, win->map->width, win->player);
	if (win->keys[XK_s] || win->keys[XK_S])
		r |= move_down(win->map->grid, win->map->width, win->player);
	if (win->keys[XK_a] || win->keys[XK_A])
		r |= move_left(win->map->grid, win->map->width, win->player);
	if (win->keys[XK_d] || win->keys[XK_D])
		r |= move_right(win->map->grid, win->map->width, win->player);
	if (win->keys[XK_Left])
		r |= rotate_left(win->player);
	if (win->keys[XK_Right])
		r |= rotate_right(win->player);
	win->player->speed = old_speed;
	return (r);
}
