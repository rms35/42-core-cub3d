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

void	animate_fire(t_sprite *s, const double delta_time)
{
	s->last_update += delta_time;
	if (s->last_update * 1000 >= s->anim_speed)
	{
		s->last_update = 0;
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

void	animate_door(t_sprite *s, const double delta_time)
{
	if (s->opening && s->door_offs < MAX_DOOR_OFFS)
	{
		s->door_offs += (DOOR_T * delta_time);
		if (s->door_offs >= MAX_DOOR_OFFS)
		{
			s->door_offs = MAX_DOOR_OFFS;
			s->opening = 0;
			s->open = 1;
		}
	}
	else if (s->closing && s->door_offs > 0)
	{
		s->door_offs -= (DOOR_T * delta_time);
		if (s->door_offs <= 0)
		{
			s->door_offs = 0;
			s->closing = 0;
		}
	}
}

void	animate_sprites(t_sprite *s, const double delta_time,
		const size_t n_sprites)
{
	size_t	i;

	i = 0;
	while (i < n_sprites && s[i].sprite_id != 0)
	{
		s[i].animation(&s[i], delta_time);
		i++;
	}
}
