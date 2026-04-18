/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 23:26:48 by rafael-m          #+#    #+#             */
/*   Updated: 2026/03/20 13:30:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	init_fires(t_sprite *s, const size_t total)
{
	size_t i;

	i = 0;
	while (i < total && s[i].sprite_id == FIRE)
	{
		if (i % 2)
			s[i].current_frame = 3;
		i++;
	}
}

bool sprites_textures(t_win *win)
{
	size_t i;

	i = 0;
	win->door = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!win->door)
		return true;
	if (load_texture(win, win->door,"textures/doors/door.xpm"))
		return true;
	while (i < N_FIRES)
	{
		win->fire[i] = (t_img *)ft_calloc(1, sizeof(t_img));
		if (!win->fire[i])
			return true;
		i++;
	}
	if (load_texture(win, win->fire[0],"textures/fire/fire1.xpm") == 1
		|| load_texture(win, win->fire[1],"textures/fire/fire2.xpm") == 1
		|| load_texture(win, win->fire[2],"textures/fire/fire3.xpm") == 1
		|| load_texture(win, win->fire[3],"textures/fire/fire4.xpm") == 1)
		return true;
	return false;
}

void init_fire_sprite(const t_win *win, const t_map *map, const size_t
	sprites, const size_t i)
{
	win->sprites[sprites].x = (double)(i % map->width) + 0.5;
	win->sprites[sprites].y = (double)(i / map->width) + 0.5;
	win->sprites[sprites].frame_count = 4;
	win->sprites[sprites].anim_speed = FIRE_T;
	win->sprites[sprites].sprite_id = FIRE;
	win->sprites[sprites].next_frame = 1;
	win->sprites[sprites].current_frame = 0;
	win->sprites[sprites].animation = animate_fire;
}

void init_door_sprites(const t_win *win, const t_map *map, const size_t
	sprites, const size_t i)
{
	win->sprites[sprites].x = (double)(i % map->width) + 0.5;
	win->sprites[sprites].y = (double)(i / map->width) + 0.5;
	win->sprites[sprites].sprite_id = DOOR;
	win->sprites[sprites].tex = win->door;
}

// TODO: Proper cleanup
int	init_sprites(t_win *win, const t_map *map)
{
	size_t	sprites;
	size_t i;

	sprites = 0;
	i = 0;
	alloc_sprites(win);
	if (sprites_textures(win))
		return (1);
	while (i < map->width * map->height)
	{
		if (map->grid[i] == 'F' && sprites < win->n_sprites)
		{
			init_fire_sprite(win, map, sprites, i);
			sprites++;
		}
		else if (map->grid[i] == 'D' && sprites < win->n_sprites)
		{
			init_door_sprites(win, map, sprites, i);
			sprites++;
		}
		i++;
	}
	init_fires(win->sprites, sprites);
	return (0);
}
