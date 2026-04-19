/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:56:33 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 18:25:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	draw_wall(const t_win *win, t_ray *ray, const int int_x, int y)
{
	int		tex_y;
	int		tex_x;
	int		color;

	tex_y = (int)ray->tex_pos % ray->tex->height;
	if (tex_y < 0)
		tex_y += ray->tex->height;
	tex_x = (int)(ray->wall_x * (double)ray->tex->width);
	if (tex_x >= ray->tex->width)
		tex_x = ray->tex->width - 1;
	if (tex_x < 0)
		tex_x = 0;
	ray->tex_pos += ray->tex_step;
	color = *(unsigned int *)(ray->tex->addr + (tex_y * ray->tex->line_len
				+ tex_x * (ray->tex->bpp / 8)));
	*(unsigned int *)(win->img->addr + (y * win->img->line_len + int_x)) =
		color;
}

static void	draw_line(const t_win *win, t_ray *ray, const int x)
{
	int	y;
	int	offset;

	y = 0;
	offset = x * (win->img->bpp / 8);
	while (y < HEIGHT)
	{
		while (y < ray->draw_start)
		{
			*(unsigned int *)(win->img->addr + (y * win->img->line_len + offset))
				= win->map->ceil_color;
			y++;
		}
		while (y < ray->draw_end)
		{
			draw_wall(win, ray, offset, y);
			y++;
		}
		while (y < HEIGHT)
		{
			*(unsigned int *)(win->img->addr + (y * win->img->line_len + offset))
				= win->map->floor_color;
			y++;
		}
	}
}

static void	get_wall(t_ray *ray, t_img *tex)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			ray->tex = &tex[W1W];
		else
			ray->tex = &tex[W1E];
	}
	else
	{
		if (ray->dir_y > 0)
			ray->tex = &tex[W1S];
		else
			ray->tex = &tex[W1N];
	}
}

void	render_frame(t_win *win)
{
	t_ray	ray;
	int		x;
	int		center_ofs;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(win, &ray, x);
		perform_dda(win, &ray);
		if (ray.perp_dist < 0.1)
			ray.perp_dist = 0.1;
		win->z_buffer[x] = ray.perp_dist;
		center_ofs = (HEIGHT / 2) + win->player->pitch;
		ray.line_height = (int)((double)HEIGHT / ray.perp_dist) / 2;
		ray.draw_start = center_ofs - (ray.line_height / 2);
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = center_ofs + (ray.line_height / 2);
		if (ray.draw_end >= HEIGHT)
			ray.draw_end = HEIGHT - 1;
		get_wall(&ray, win->textures);
		ray.tex_step = 1.0 * ray.tex->height / ray.line_height;
		ray.tex_pos = (ray.draw_start - center_ofs + ray.line_height / 2) *
			ray.tex_step;
		draw_line(win, &ray, x);
		x++;
	}
	render_sprites(win);
	render_hud(win);
	animate_sprites(win->sprites,  get_time() * 1000, win->n_sprites);
}