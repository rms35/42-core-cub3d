/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 16:25:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	get_dir(t_player *p, char c)
{
	if (c == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
	}
	else if (c == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
	}
	else if (c == 'W')
	{
		p->dir_x = 1;
		p->dir_y = 0;
	}
	else if (c == 'E')
	{
		p->dir_x = -1;
		p->dir_y = 0;
	}
}

static void	init_player_values(t_player *p, double fov)
{
	p->camp_x = -p->dir_y * (tan(fov / 2.0));
	p->camp_y = p->dir_x * (tan(fov / 2.0));
	p->speed = P1_SPEED;
	p->rot_speed = P1_TURNSP;
	p->cos_r = cos(p->rot_speed);
	p->sin_r = sin(p->rot_speed);
	p->cos_l = cos(-p->rot_speed);
	p->sin_l = sin(-p->rot_speed);
	p->fov = fov;
	p->dir_mag = sqrt(p->dir_x * p->dir_x + p->dir_y * p->dir_y);
	p->radius = P1_R;
	p->fwd_speed = P1_SPEED;
	p->rot_speed = P1_ROT_SPEED;
}

void	init_player(t_player *p, const t_map *map, const double fov)
{
	size_t	i;

	ft_bzero(p, sizeof(t_player));
	i = 0;
	while (i < map->width * map->height)
	{
		if (map->grid[i] != '\0' && ft_strchr(PLYR_DIR, map->grid[i]))
			break ;
		i++;
	}
	if (i >= map->width * map->height)
	{
		write(2, "Error: No player found in map\n", 30);
		exit(1);
	}
	p->pos_x = (double)(i % map->width) + 0.5;
	p->pos_y = (double)(i / map->width) + 0.5;
	get_dir(p, map->grid[i]);
	map->grid[i] = '0';
	init_player_values(p, fov);
}
