/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 20:55:44 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	handle_mouse_rotation(const t_win *win)
{
	if (win->player->m_delta_x != 0)
	{
		rot_x_axis(win->player, (double)win->player->m_delta_x * M_SENS);
		win->player->m_delta_x = 0;
	}
	if (win->player->m_delta_y != 0)
	{
		win->player->pitch -= win->player->m_delta_y;
		if (win->player->pitch > 400)
			win->player->pitch = 400;
		if (win->player->pitch < -400)
			win->player->pitch = -400;
		win->player->m_delta_y = 0;
	}
}

t_sprite	*get_door(t_sprite *s, size_t n_sprites, int next_x, int next_y)
{
	size_t	i;

	i = 0;
	while (i < n_sprites)
	{
		if (s[i].sprite_id == DOOR && (int)floor(s[i].x) == next_x
			&& (int)floor(s[i].y) == next_y)
			return (&s[i]);
		i++;
	}
	return (NULL);
}

static void	handle_door_state(t_sprite *door)
{
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

void	open_door(const t_win *win)
{
	int			next_x;
	int			next_y;
	double		dist_x;
	double		dist_y;
	t_sprite	*door;

	next_y = (int)(win->player->pos_y + win->player->dir_y);
	next_x = (int)(win->player->pos_x + win->player->dir_x);

	if (win->map->grid[next_y * win->map->width + next_x] == 'D')
	{
		door = get_door(win->sprites, win->n_sprites, next_x, next_y);
		if (!door)
			return ;
		dist_x = win->player->pos_x - door->x;
		dist_y = win->player->pos_y - door->y;
		if (sqrt(dist_x * dist_x + dist_y * dist_y) < 0.7)
			handle_door_state(door);
	}
}
