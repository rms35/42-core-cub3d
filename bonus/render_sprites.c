/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:25:32 by rafael-m          #+#    #+#             */
/*   Updated: 2026/03/19 15:45:00 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

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

static void	sort_sprites(const t_win *win)
{
	t_pair	pairs[N_SPRITES];
	double	dx;
	double	dy;
	int		i;

	i = 0;
	while (i < N_SPRITES)
	{
		dx = win->player->pos_x - win->sprites[i].x;
		dy = win->player->pos_y - win->sprites[i].y;
		pairs[i].dist = (dx * dx) + (dy * dy);
		pairs[i].index = i;
		i++;
	}
	qsort(pairs, N_SPRITES, sizeof(t_pair), compare_sprites);
	i = 0;
	while (i < N_SPRITES)
	{
		win->sprite_order[i] = pairs[i].index;
		win->sprite_dist[i] = pairs[i].dist;
		i++;
	}
}

static void	calculate_draw_params(const t_win *win, const t_sprite *s, t_sprite_draw *d)
{
	d->sprite_height = abs((int)(HEIGHT / s->trans_y)) / 2;
	d->draw_start_y = -d->sprite_height / 2 + HEIGHT / 2 + win->player->pitch;
	if (d->draw_start_y < 0)
		d->draw_start_y = 0;
	d->draw_end_y = d->sprite_height / 2 + HEIGHT / 2 + win->player->pitch;
	if (d->draw_end_y >= HEIGHT)
		d->draw_end_y = HEIGHT - 1;
	d->sprite_width = abs((int)(HEIGHT / s->trans_y)) / 2;
	d->sprite_screen_x = (int)((WIDTH / 2) * (1 + s->trans_x / s->trans_y));
	d->draw_start_x = -d->sprite_width / 2 + d->sprite_screen_x;
	if (d->draw_start_x < 0)
		d->draw_start_x = 0;
	d->draw_end_x = d->sprite_width / 2 + d->sprite_screen_x;
	if (d->draw_end_x >= WIDTH)
		d->draw_end_x = WIDTH - 1;
}

unsigned int	alpha_blend(unsigned int background, unsigned int foreground, float alpha)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	r = (unsigned int)((((background >> 16) & 0xFF) * (1.0 - alpha))
			+ (((foreground >> 16) & 0xFF) * alpha));
	g = (unsigned int)((((background >> 8) & 0xFF) * (1.0 - alpha))
			+ (((foreground >> 8) & 0xFF) * alpha));
	b = (unsigned int)(((background & 0xFF) * (1.0 - alpha))
			+ ((foreground & 0xFF) * alpha));
	return ((r << 16) | (g << 8) | b);
}

static void	draw_sprite_stripe(const t_win *win, const t_sprite *s, t_sprite_draw *d, int x)
{
	t_img			*tex;
	int				y;
	int				d_y;
	unsigned int	color;
	unsigned int	*dest;

	tex = &s->tex[s->current_frame];
	d->tex_x = (int)(256 * (x - (-d->sprite_width / 2 + d->sprite_screen_x))
			* tex->width / d->sprite_width) / 256;
	if (d->tex_x < 0 || d->tex_x >= tex->width)
		return ;
	y = d->draw_start_y;
	while (y < d->draw_end_y)
	{
		d_y = (y - win->player->pitch) * 256 - HEIGHT * 128
			+ d->sprite_height * 128;
		d->tex_y = ((d_y * tex->height) / d->sprite_height) / 256;
		if (d->tex_y < 0)
			d->tex_y = 0;
		if (d->tex_y >= tex->height)
			d->tex_y = tex->height - 1;
		color = ((unsigned int *)tex->addr)[d->tex_y * (tex->line_len / 4)
			+ d->tex_x];
		if ((color & 0x00FFFFFF) != 0)
		{
			dest = (unsigned int *)win->img->addr + (y * (win->img->line_len / 4) + x);
			if (s->sprite_id == FIRE && ((color >> 16) & 0xFF) > 150
				&& ((color >> 8) & 0xFF) > 100)
				*dest = alpha_blend(*dest, color, 0.7);
			else
				*dest = color;
		}
		y++;
	}
}

static void	calc_sprite_pos(const t_win *win, t_sprite *s, const double inv_det)
{
	double	spr_x;
	double	spr_y;

	spr_x = s->x - win->player->pos_x;
	spr_y = s->y - win->player->pos_y;
	s->trans_x = inv_det * (win->player->dir_y * spr_x
			- win->player->dir_x * spr_y);
	s->trans_y = inv_det * (-win->player->camp_y * spr_x
			+ win->player->camp_x * spr_y);
}

void	render_sprites(const t_win *win)
{
	t_sprite_draw	d;
	t_sprite		*s;
	double			inv_det;
	int				i;
	int				stripe;

	sort_sprites(win);
	inv_det = 1.0 / (win->player->camp_x * win->player->dir_y
			- win->player->dir_x * win->player->camp_y);
	i = -1;
	while (++i < N_SPRITES)
	{
		s = &win->sprites[win->sprite_order[i]];
		calc_sprite_pos(win, s, inv_det);
		if (s->trans_y <= 0 || !s->tex)
			continue ;
		calculate_draw_params(win, s, &d);
		stripe = d.draw_start_x - 1;
		while (++stripe < d.draw_end_x)
			if (s->trans_y < win->z_buffer[stripe])
				draw_sprite_stripe(win, s, &d, stripe);
	}
}
