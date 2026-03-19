/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:25:32 by rafael-m          #+#    #+#             */
/*   Updated: 2026/03/17 11:25:32 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	get_sprites_dist(const t_win *win)
{
	int		i;
	double	dx;
	double	dy;

	i = 0;
	while (i < N_SPRITES)
	{
		dx = win->player->pos_x - win->sprites[i].x;
		dy = win->player->pos_y - win->sprites[i].y;
		win->sprite_dist[i] = (dx * dx) + (dy * dy);
		win->sprite_order[i] = i;
		i++;
	}
}

static void	sort_sprites(const t_win *win)
{
	int		i;
	int		j;
	double	tmp_dist;
	int		tmp_order;

	i = 0;
	while (i < N_SPRITES)
	{
		j = 0;
		while (j < N_SPRITES - i - 1)
		{
			if (win->sprite_dist[j] < win->sprite_dist[j + 1])
			{
				tmp_dist = win->sprite_dist[j];
				win->sprite_dist[j] = win->sprite_dist[j + 1];
				win->sprite_dist[j + 1] = tmp_dist;
				tmp_order = win->sprite_order[j];
				win->sprite_order[j] = win->sprite_order[j + 1];
				win->sprite_order[j + 1] = tmp_order;
			}
			j++;
		}
		i++;
	}
}

static void	calculate_sprite_draw_params(const t_win *win, const t_sprite
	*s, t_sprite_draw *d)
{
	d->sprite_height = abs((int)(HEIGHT / s->trans_y));
	d->draw_start_y = -d->sprite_height / 2 + HEIGHT / 2 + win->player->pitch;
	if (d->draw_start_y < 0)
		d->draw_start_y = 0;
	d->draw_end_y = d->sprite_height / 2 + HEIGHT / 2 + win->player->pitch;
	if (d->draw_end_y >= HEIGHT)
		d->draw_end_y = HEIGHT - 1;
	d->sprite_width = abs((int)(HEIGHT / s->trans_y));
	d->sprite_screen_x = (int)((WIDTH / 2) * (1 + s->trans_x / s->trans_y));
	d->draw_start_x = -d->sprite_width / 2 + d->sprite_screen_x;
	if (d->draw_start_x < 0)
		d->draw_start_x = 0;
	d->draw_end_x = d->sprite_width / 2 + d->sprite_screen_x;
	if (d->draw_end_x >= WIDTH)
		d->draw_end_x = WIDTH - 1;
}
static void	draw_sprite_stripe(const t_win *win, const t_sprite *s,
	t_sprite_draw *d, int x)
{
	int				y;
	int				d_val;
	unsigned int	color;
	int				offset;

	y = d->draw_start_y;
	offset = x * (win->img->bpp / 8);
	while (y < d->draw_end_y)
	{
		d_val = (y - win->player->pitch) * 256 - HEIGHT * 128
			+ d->sprite_height * 128;
		d->tex_y = (((d_val * s->tex.height) / d->sprite_height) / 256)
			& (s->tex.height - 1);
		color = *(unsigned int *)(s->tex.addr + (d->tex_y
					* s->tex.line_len + (d->tex_x & (s->tex.width - 1))
					* (s->tex.bpp / 8)));
		if ((color & 0x00FFFFFF) != 0)
			*(unsigned int *)(win->img->addr + (y * win->img->line_len
						+ offset)) = color;
		y++;
	}
}

void	render_sprites(const t_win *win)
{
	t_player		*p;
	t_sprite		*s;
	t_sprite_draw	d;
	int				i;
	int				stripe;
	double			inv_det;
	double			spr_x;
	double			spr_y;

	get_sprites_dist((t_win *)win);
	sort_sprites((t_win *)win);
	p = win->player;
	inv_det = 1.0 / (p->camp_x * p->dir_y - p->dir_x * p->camp_y);
	i = -1;
	while (++i < N_SPRITES)
	{
		s = &win->sprites[win->sprite_order[i]];
		spr_x = s->x - p->pos_x;
		spr_y = s->y - p->pos_y;
		s->trans_x = inv_det * (p->dir_y * spr_x - p->dir_x * spr_y);
		s->trans_y = inv_det * (-p->camp_y * spr_x + p->camp_x * spr_y);
		if (s->trans_y <= 0)
			continue ;
		calculate_sprite_draw_params((t_win *)win, s, &d);
		stripe = d.draw_start_x - 1;
		while (++stripe < d.draw_end_x)
		{
			d.tex_x = (int)(256 * (stripe - (-d.sprite_width / 2
							+ d.sprite_screen_x)) * s->tex.width
					/ d.sprite_width) / 256;
			if (s->trans_y < win->z_buffer[stripe])
				draw_sprite_stripe((t_win *)win, s, &d, stripe);
		}
	}
}