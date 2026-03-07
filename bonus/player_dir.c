/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 13:16:14 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 19:50:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	rotate_player(t_player *p, const double angle)
{
	double	old_dir_x;
	double	old_camp_x;
	double	c;
	double	s;

	c = cos(angle);
	s = sin(angle);
	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * c - p->dir_y * s;
	p->dir_y = old_dir_x * s + p->dir_y * c;
	old_camp_x = p->camp_x;
	p->camp_x = p->camp_x * c - p->camp_y * s;
	p->camp_y = old_camp_x * s + p->camp_y * c;
	return (1);
}

int	rotate_left(t_player *player)
{
	return (rotate_player(player, -player->turn_speed));
}

int	rotate_right(t_player *player)
{
	return (rotate_player(player, player->turn_speed));
}
