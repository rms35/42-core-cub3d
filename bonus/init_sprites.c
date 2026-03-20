/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 23:26:48 by rafael-m          #+#    #+#             */
/*   Updated: 2026/03/20 11:43:27 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_fires(t_sprite *s)
{
	int i;

	i = 0;
	while ((s + i)->sprite_id == FIRE)
	{
		if (i % 2)
			(s + i)->current_frame = 3;
		i++;
	}
}

// TODO: Proper cleanup
int	init_sprites(t_win *win, const t_map *map)
{
	int				i;
	int				sprites;

	i = 0;
	sprites = 0;
	if (alloc_sprites(win))
		return (1);
	while (i < map->width * map->height)
	{
		if (map->grid[i] == 'F' && sprites < N_SPRITES)
		{
			win->sprites[sprites].x = (double)(i % map->width) + 0.5;
			win->sprites[sprites].y = (double)(i / map->width) + 0.5;
			win->sprites[sprites].sprite_id = FIRE;
			if (sprites == 0)
			{
				if (load_texture(win, &win->sprites[sprites].tex[0],
					"textures/fire1.xpm") == 1
					|| load_texture(win, &win->sprites[sprites].tex[1],
						"textures/fire2.xpm") == 1
					|| load_texture(win, &win->sprites[sprites].tex[2],
						"textures/fire3.xpm") == 1
					|| load_texture(win, &win->sprites[sprites].tex[3],
						"textures/fire4.xpm") == 1)
					return (1);
			}
			else
			{
				win->sprites[sprites].tex[0] = win->sprites[0].tex[0];
				win->sprites[sprites].tex[1] = win->sprites[0].tex[1];
				win->sprites[sprites].tex[2] = win->sprites[0].tex[2];
				win->sprites[sprites].tex[3] = win->sprites[0].tex[3];
			}
			win->sprites[sprites].frame_count = 4;
			win->sprites[sprites].anim_speed = FIRE_T;
			win->sprites[sprites].sprite_id = FIRE;
			win->sprites[sprites].next_frame = 1;
			win->sprites[sprites].current_frame = 0;
			// win->sprites[sprites].res = FIRES_SIZE;
			win->sprites[sprites].animation = animate_fire;
			sprites++;
		}
		init_fires(win->sprites);
		i++;
	}
	return (0);
}