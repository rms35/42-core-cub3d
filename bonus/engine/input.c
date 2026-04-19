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

t_sprite	*get_door(t_sprite *s, const size_t n_sprites, const int next_x,
	const int next_y)
{
	size_t	i;

	i = 0;
	while (i < n_sprites)
	{
		if (s[i].sprite_id == DOOR && floor(s[i].x) == next_x && floor(s[i]
			.y) == next_y)
				return (&s[i]);
		i++;
	}
	return (NULL);
}

void	open_door(const t_win *win)
{
	int			next_x;
	int			next_y;
	t_sprite	*door;

	next_y = (int)(win->player->pos_y + win->player->dir_y);
	next_x = (int)(win->player->pos_x + win->player->dir_x);
	if (win->map->grid[next_y * win->map->width + next_x] == 'D')
	{
		door = get_door(win->sprites, win->n_sprites, next_x, next_y);
		if (!door)
			return ;
		if (!door->closing && !door->opening)
		{
			if (door->open)
			{
				door->closing = 1;
				door->open = 0;
			}
			else
				door->opening = 1;
		}
	}
}

int	key_press(int keysym, const void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (keysym == KEY_ESC)
		close_win(win);
	if (keysym < N_KEYS)
		win->keys[keysym] = 1;
	return (0);
}

int	key_release(const int keysym, const void *param)
{
	t_win	*win;

	win = (t_win *)param;
	if (keysym < N_KEYS)
		win->keys[keysym] = 0;
	return (0);
}

static void	update_dir(const t_win *win, const t_player *p, double *dx, double *dy)
{
	double move_speed;

	move_speed= win->player->speed * win->delta_time;
	if (win->keys[KEY_W])
	{
		move_speed= win->player->fwd_speed * win->delta_time;
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
		r = move_player(win, dx, dy);
	if (win->keys[KEY_SHIFT])
		win->player->fwd_speed = 2.5 * P1_SPEED;
	else
		win->player->fwd_speed = P1_SPEED;
	if (win->keys[KEY_E])
		open_door(win);
	return (r);
}
