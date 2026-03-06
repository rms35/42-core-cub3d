/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 17:00:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_map(const t_map *map)
{
	int	i;
	int	total;

	total = map->height * map->width;
	i = 0;
	while (i < total)
	{
		printf("%c ", map->grid[i]);
		if (i != 0 && (i + 1) % map->width == 0)
			printf("\n");
		i++;
	}
	write(1, "\n", 1);
}

void	init_player(t_player *p, char *grid, int width, int total)
{
	int	i;

	i = 0;
	while (i < total && (grid[i] == '1' || grid[i] == '0'))
		i++;
	p->grid_pos = i;
	p->pos_x = (double)(i % width) + 0.5;
	p->pos_y = (double)(i / width) + 0.5;
	grid[i] = '0';
	p->dir_x = 0.0;
	p->dir_y = 1.0;
	p->camp_mod = 0.66;
	p->camp_x = -0.66;
	p->camp_y = 0.0;
	p->speed = 0.01;
	p->turn_speed = 0.0075;
	p->cos_r = cos(p->turn_speed);
	p->sin_r = sin(p->turn_speed);
	p->cos_l = cos(-p->turn_speed);
	p->sin_l = sin(-p->turn_speed);
}

int	key_press(const int keysym, t_win *win)
{
	if (keysym == XK_Escape)
		close_win(win, EXIT_SUCCESS);
	if (keysym < 65536)
		win->keys[keysym] = 1;
	return (0);
}

int	key_release(const int keysym, t_win *win)
{
	if (keysym < 65536)
		win->keys[keysym] = 0;
	return (0);
}
