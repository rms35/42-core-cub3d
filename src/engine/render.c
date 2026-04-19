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

#include "../../includes/cub3d.h"

static void	draw_wall(const t_win *win, t_ray *ray, int offset, int y)
{
	int		tex_y;
	int		tex_x;
	t_img	*tex;

	tex = (t_img *)&win->textures[ray->wall_tex];
	tex_y = (int)ray->tex_pos % tex->height;
	if (tex_y < 0)
		tex_y += tex->height;
	tex_x = (int)(ray->wall_x * (double)tex->width);
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	ray->tex_pos += ray->tex_step;
	*(unsigned int *)(win->img->addr + (y * win->img->line_len + offset))
		= *(unsigned int *)(tex->addr + (tex_y * tex->line_len
				+ tex_x * (tex->bpp / 8)));
}

static void	draw_line(const t_win *win, t_ray *ray, int x)
{
	int	y;
	int	offset;

	y = 0;
	offset = x * (win->img->bpp / 8);
	while (y < HEIGHT)
	{
		while (y < ray->draw_start)
		{
			*(unsigned int *)(win->img->addr + (y * win->img->line_len
						+ offset)) = win->map->ceil_color;
			y++;
		}
		while (y < ray->draw_end)
		{
			draw_wall(win, ray, offset, y);
			y++;
		}
		while (y < HEIGHT)
		{
			*(unsigned int *)(win->img->addr + (y * win->img->line_len
						+ offset)) = win->map->floor_color;
			y++;
		}
	}
}

static void	get_wall_texture(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			ray->wall_tex = TEX_WEST;
		else
			ray->wall_tex = TEX_EAST;
	}
	else
	{
		if (ray->dir_y > 0)
			ray->wall_tex = TEX_SOUTH;
		else
			ray->wall_tex = TEX_NORTH;
	}
}

static void	render_column(const t_win *win, t_ray *ray, int x, int height)
{
	init_ray(win, ray, x);
	perform_dda(win, ray);
	if (ray->perp_dist < 0.1)
		ray->perp_dist = 0.1;
	ray->line_height = (int)((double)height / ray->perp_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	get_wall_texture(ray);
	ray->tex_step = 1.0 * win->textures[ray->wall_tex].height
		/ ray->line_height;
	ray->tex_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* ray->tex_step;
	draw_line(win, ray, x);
}

void	render_frame(const t_win *win)
{
	t_ray	ray;
	int		x;
	int		height;

	x = 0;
	height = HEIGHT / 2;
	while (x < WIDTH)
	{
		render_column(win, &ray, x, height);
		x++;
	}
}
