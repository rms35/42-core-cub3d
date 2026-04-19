/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:00:00 by rafael-m          #+#    #+#             */
/*   Updated: 2026/04/19 14:20:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	animate_fire(t_sprite *s, const double time)
{
	if (time - s->last_update >= s->anim_speed)
	{
		s->last_update = time;
		if (s->current_frame == 0)
		{
			s->current_frame = 1;
			s->next_frame = 1;
		}
		else if (s->current_frame == N_FIRES - 1)
		{
			s->current_frame = 2;
			s->next_frame = -1;
		}
		else
			s->current_frame += s->next_frame;
	}
}

static void	update_door_state(t_sprite *s, double door_speed,
		double max_offset, double time)
{
	if (s->opening && s->door_offs < max_offset)
	{
		s->door_offs += (door_speed * time);
		if (s->door_offs >= max_offset)
		{
			s->door_offs = max_offset;
			s->opening = 0;
			s->open = 1;
		}
	}
	else if (s->closing && s->door_offs > 0)
	{
		s->door_offs -= (door_speed * time);
		if (s->door_offs <= 0)
		{
			s->door_offs = 0;
			s->closing = 0;
		}
	}
}

void	animate_door(t_sprite *s, const double time)
{
	double	door_speed;
	double	max_door_offset;

	door_speed = 0.0000000005;
	max_door_offset = 0.77;
	update_door_state(s, door_speed, max_door_offset, time);
}

void	animate_sprites(t_sprite *s, const double time, const size_t n_sprites)
{
	size_t	i;

	i = 0;
	while (i < n_sprites && s[i].sprite_id != 0)
	{
		s[i].animation(&s[i], time);
		i++;
	}
}
