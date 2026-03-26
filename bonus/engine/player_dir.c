/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 13:16:14 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 17:00:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

void	rot_x_axis(t_player *p, const double angle)
{
	double	old_dir_x;
	double	old_camp_x;

	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(angle) - p->dir_y * sin(angle);
	p->dir_y = old_dir_x * sin(angle) + p->dir_y * cos(angle);
	old_camp_x = p->camp_x;
	p->camp_x = p->camp_x * cos(angle) - p->camp_y * sin(angle);
	p->camp_y = old_camp_x * sin(angle) + p->camp_y * cos(angle);
	p->dir_mag = sqrt(p->dir_x * p->dir_x + p->dir_y * p->dir_y);
}
