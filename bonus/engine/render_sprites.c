/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_sprites.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 11:25:32 by rafael-m          #+#    #+#             */
/*   Updated: 2026/04/19 16:55:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	apply_sprite_pixel(t_sprite *sprite, unsigned int *dest,
	unsigned int color)
{
	if ((color & 0x00FFFFFF) != 0)
	{
		if ((sprite->sprite_id == FIRE) && ((color >> 16) & 0xFF) > 150
			&& ((color >> 8) & 0xFF) > 100)
			*dest = alpha_blend(*dest, color, 0.7);
		else
			*dest = color;
	}
}

static void	draw_sprite_pixel(t_win *win, t_sprite *sprite, t_sprite_draw *draw,
	int x)
{
	t_img			*tex;
	unsigned int	color;
	double			t_pos;
	double			t_step;
	int				y;
	unsigned int	*dest;
	int				line_stride;

	tex = &sprite->tex[sprite->current_frame];
	t_step = 1.0 * tex->height / draw->sprite_height;
	y = draw->draw_start_y;
	t_pos = (y - win->player->pitch - HEIGHT / 2.0
			+ draw->sprite_height / 2.0) * t_step;
	line_stride = win->img->line_len / 4;
	dest = (unsigned int *)win->img->addr + (y * line_stride + x);
	while (y < draw->draw_end_y)
	{
		draw->tex_y = (int)t_pos;
		if (draw->tex_y < 0)
			draw->tex_y = 0;
		else if (draw->tex_y >= tex->height)
			draw->tex_y = tex->height - 1;
		color = ((unsigned int *)tex->addr)[draw->tex_y * (tex->line_len / 4)
			+ draw->tex_x];
		apply_sprite_pixel(sprite, dest, color);
		t_pos += t_step;
		dest += line_stride;
		y++;
	}
}

static void	calc_sprite_pos(t_win *win, t_sprite *sprite, double inv_det)
{
	double	sprite_x;
	double	sprite_y;

	sprite_x = sprite->x - win->player->pos_x;
	sprite_y = sprite->y - win->player->pos_y;
	sprite->trans_x = inv_det * (win->player->dir_y * sprite_x
			- win->player->dir_x * sprite_y);
	sprite->trans_y = inv_det * (-win->player->camp_y * sprite_x
			+ win->player->camp_x * sprite_y);
}

static void	draw_stripes(t_win *win, t_sprite *sprite, t_sprite_draw *draw)
{
	int		stripe;
	t_img	*texture;
	int		start_x;
	double	tex_step;
	double	tex_pos;

	stripe = draw->draw_start_x;
	texture = &sprite->tex[sprite->current_frame];
	start_x = -draw->sprite_width / 2 + draw->sprite_screen_x;
	tex_step = 1.0 * texture->width / draw->sprite_width;
	tex_pos = (stripe - start_x) * tex_step;
	while (stripe < draw->draw_end_x)
	{
		draw->tex_x = (int)tex_pos;
		if (sprite->trans_y < win->z_buffer[stripe]
			&& draw->tex_x >= 0 && draw->tex_x < texture->width)
			draw_sprite_pixel(win, sprite, draw, stripe);
		tex_pos += tex_step;
		stripe++;
	}
}

void	render_sprites(t_win *win)
{
	t_sprite_draw	draw;
	t_sprite		*sprite;
	double			inv_det;
	size_t			index;

	sort_sprites(win);
	inv_det = 1.0 / (win->player->camp_x * win->player->dir_y
			- win->player->dir_x * win->player->camp_y);
	index = 0;
	while (index < win->n_sprites)
	{
		sprite = &win->sprites[win->sprite_order[index]];
		calc_sprite_pos(win, sprite, inv_det);
		if (sprite->trans_y > 0 && sprite->tex && sprite->sprite_id != DOOR)
		{
			calculate_draw_params(win, sprite, &draw);
			draw_stripes(win, sprite, &draw);
		}
		else if (sprite->trans_y > 0 && sprite->sprite_id == DOOR)
			render_door(win, sprite);
		index++;
	}
}
