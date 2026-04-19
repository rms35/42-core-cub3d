/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 23:26:48 by rafael-m          #+#    #+#             */
/*   Updated: 2026/04/19 14:50:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	init_fires_frames(t_sprite *sprites, size_t total)
{
	size_t	i;

	i = 0;
	while (i < total)
	{
		if (sprites[i].sprite_id == FIRE)
		{
			if (i % 2)
				sprites[i].current_frame = 3;
		}
		i++;
	}
}

static int	load_fire_textures(t_win *win)
{
	if (load_texture(win, &win->fire[0], "textures/fire/fire1.xpm")
		|| load_texture(win, &win->fire[1], "textures/fire/fire2.xpm")
		|| load_texture(win, &win->fire[2], "textures/fire/fire3.xpm")
		|| load_texture(win, &win->fire[3], "textures/fire/fire4.xpm"))
		return (1);
	return (0);
}

static int	load_sprites_textures(t_win *win)
{
	win->door = (t_img *)ft_calloc(1, sizeof(t_img));
	if (!win->door)
		return (1);
	if (load_texture(win, win->door, "textures/doors/door.xpm"))
		return (1);
	if (load_fire_textures(win))
		return (1);
	return (0);
}

static void	init_sprite_data(t_sprite *s, t_map *map, size_t i, int id)
{
	s->x = (double)(i % map->width) + 0.5;
	s->y = (double)(i / map->width) + 0.5;
	s->sprite_id = id;
	if (id == FIRE)
	{
		s->frame_count = 4;
		s->anim_speed = FIRE_T;
		s->next_frame = 1;
		s->current_frame = 0;
		s->animation = animate_fire;
	}
	else if (id == DOOR)
		s->animation = animate_door;
}

int	init_sprites(t_win *win, t_map *map)
{
	size_t	sprites_count;
	size_t	i;

	sprites_count = 0;
	i = 0;
	alloc_sprites(win);
	if (load_sprites_textures(win))
		return (1);
	while (i < map->width * map->height)
	{
		if (map->grid[i] == 'F' && sprites_count < win->n_sprites)
		{
			init_sprite_data(&win->sprites[sprites_count], map, i, FIRE);
			win->sprites[sprites_count++].tex = win->fire;
		}
		else if (map->grid[i] == 'D' && sprites_count < win->n_sprites)
		{
			init_sprite_data(&win->sprites[sprites_count], map, i, DOOR);
			win->sprites[sprites_count++].tex = win->door;
		}
		i++;
	}
	init_fires_frames(win->sprites, sprites_count);
	return (0);
}
