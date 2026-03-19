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
		else if (s->current_frame == SPRT1_N - 1)
		{
			s->current_frame = 2;
			s->next_frame = -1;
		}
		else
			s->current_frame += s->next_frame;
	}
}