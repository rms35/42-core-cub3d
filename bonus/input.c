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

#include "../includes/cub3d.h"

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

int	handle_input(t_win *win)
{
	double	d[2];
	double	s;
	int		moved;

	process_mouse(win);
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
	{
		if (win->player->walk_t > 0)
			win->player->walk_t -= 0.1;
		if (win->player->walk_t < 0)
			win->player->walk_t = 0;
	}
	return (moved);
}
