/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 12:00:00 by rafael-m          #+#    #+#             */
/*   Updated: 2026/03/19 12:00:00 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	animate_fire(t_sprite *s, const long time)
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

void animate_sprites(t_sprite *s, const long time)
{
	int	i;

	i = 0;
	while (i < N_SPRITES && s[i].sprite_id != 0)
	{
		s[i].animation(s + i, time);
		i++;
	}
}