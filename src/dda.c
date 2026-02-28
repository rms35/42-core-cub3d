/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:56:33 by rafael-m          #+#    #+#             */
/*   Updated: 2026/02/27 21:56:39 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_(t_player *player, const double width, t_img *view)
{
	t_ray	ray;
	double camera_x;
	double	i;

	i = 0.0;
	player->camp_x = -player->dir_y * player->camp_mod;
	player->camp_y = player->dir_x * player->camp_mod;
	while (i < width - 1)
	{
		camera_x = (2 * i) / width - 1;
		ray.x = player->dir_x + (player->camp_x * camera_x);
		ray.y = player->dir_y + (player->camp_y * camera_x);
		i += 1.0;
	}
}