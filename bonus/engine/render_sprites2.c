/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/23 19:36:01 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	compare_sprites(const void *a, const void *b)
{
	double	diff;

	diff = ((t_pair *)b)->dist - ((t_pair *)a)->dist;
	if (diff > 0)
		return (1);
	if (diff < 0)
		return (-1);
	return (0);
}

void	calculate_sprite_distances(t_win *win, t_pair *pairs)
{
	double	delta_x;
	double	delta_y;
	size_t	index;

	index = 0;
	while (index < win->n_sprites)
	{
		delta_x = win->player->pos_x - win->sprites[index].x;
		delta_y = win->player->pos_y - win->sprites[index].y;
		pairs[index].dist = (delta_x * delta_x) + (delta_y * delta_y);
		pairs[index].index = index;
		index++;
	}
}

void	sort_sprites(t_win *win)
{
	size_t	index;

	if (!win->pairs)
		return ;
	calculate_sprite_distances(win, win->pairs);
	qsort(win->pairs, win->n_sprites, sizeof(t_pair), compare_sprites);
	index = 0;
	while (index < win->n_sprites)
	{
		win->sprite_order[index] = win->pairs[index].index;
		win->sprite_dist[index] = win->pairs[index].dist;
		index++;
	}
}

void	calculate_draw_params(t_win *win, t_sprite *sprite,
	t_sprite_draw *draw)
{
	draw->sprite_height = ft_abs((int)(HEIGHT / sprite->trans_y)) / 2;
	draw->draw_start_y = -draw->sprite_height / 2 + HEIGHT / 2
		+ win->player->pitch;
	if (draw->draw_start_y < 0)
		draw->draw_start_y = 0;
	draw->draw_end_y = draw->sprite_height / 2 + HEIGHT / 2
		+ win->player->pitch;
	if (draw->draw_end_y >= HEIGHT)
		draw->draw_end_y = HEIGHT - 1;
	draw->sprite_width = ft_abs((int)(HEIGHT / sprite->trans_y)) / 2;
	draw->sprite_screen_x = (int)((WIDTH / 2)
			* (1 + sprite->trans_x / sprite->trans_y));
	draw->draw_start_x = -draw->sprite_width / 2 + draw->sprite_screen_x;
	if (draw->draw_start_x < 0)
		draw->draw_start_x = 0;
	draw->draw_end_x = draw->sprite_width / 2 + draw->sprite_screen_x;
	if (draw->draw_end_x >= WIDTH)
		draw->draw_end_x = WIDTH - 1;
}
