/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_dir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 13:16:14 by rafael-m          #+#    #+#             */
/*   Updated: 2026/03/01 14:03:39 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	rotate_left(t_player *player)
{
	double    old_dir_x;
	double    old_camp_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * player->cos_l - player->dir_y *player->sin_l;
	player->dir_y = old_dir_x * player->sin_l + player->dir_y * player->cos_l;
	old_camp_x = player->camp_x;
	player->camp_x = player->camp_x * player->cos_l - player->camp_y *
		player->sin_l;
	player->camp_y = old_camp_x * player->sin_l + player->camp_y *
		player->cos_l;
	return (1);
}

int	rotate_right(t_player *player)
{
	double    old_dir_x;
	double    old_camp_x;

	old_dir_x = player->dir_x;
	player->dir_x = player->dir_x * player->cos_r - player->dir_y *
		player->sin_r;
	player->dir_y = old_dir_x * player->sin_r + player->dir_y *
		player->cos_r;
	old_camp_x = player->camp_x;
	player->camp_x = player->camp_x * player->cos_r - player->camp_y *
		player->sin_r;
	player->camp_y = old_camp_x * player->sin_r + player->camp_y *
		player->cos_r;
	return (1);
}