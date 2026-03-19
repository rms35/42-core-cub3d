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

#include "../includes/cub3d_bonus.h"

static void	draw_wall(t_win *win, t_ray *ray, const int int_x, int y)
{
	int		tex_y;
	int		tex_x;
	int		color;
	t_img	*tex;

	tex = &win->textures[ray->wall_tex];
	tex_y = (int)ray->tex_pos & (TEX_HEIGHT - 1);
	tex_x = (int)(ray->wall_x * (double)TEX_WIDTH);
	ray->tex_pos += ray->tex_step;
	color = *(unsigned int *)(tex->addr + (tex_y * tex->line_len
				+ tex_x * (tex->bpp / 8)));
	*(unsigned int *)(win->img->addr + (y * win->img->line_len + int_x)) =
		color;
}

static void	draw_line(t_win *win, t_ray *ray, const int x)
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

static void	get_wall(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			ray->wall_tex = W1W;
		else
			ray->wall_tex = W1E;
	}
	else
	{
		if (ray->dir_y > 0)
			ray->wall_tex = W1S;
		else
			ray->wall_tex = W1N;
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
		if (ray.perp_wall_dist < 0.1)
			ray.perp_wall_dist = 0.1;
		win->z_buffer[x] = ray.perp_wall_dist;
		center_ofs = (HEIGHT / 2) + win->player->pitch;
		ray.line_height = (int)((double)HEIGHT / ray.perp_wall_dist) / 2;
		ray.draw_start = center_ofs - (ray.line_height / 2);
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = center_ofs + (ray.line_height / 2);
		if (ray.draw_end >= HEIGHT)
			ray.draw_end = HEIGHT - 1;
		ray.tex_step = 1.0 * TEX_HEIGHT / ray.line_height;
		ray.tex_pos = (ray.draw_start - center_ofs + ray.line_height / 2) *
			ray.tex_step;
		get_wall(&ray);
		draw_line(win, &ray, x);
		x++;
	}
	render_sprites(win);
}
//
// void	init_ray_fe(t_ray *ray, const t_player *player, const int x)
// {
// 	double alpha;
//
// 	alpha = (x - WIDTH /2) * (player->fov / WIDTH);
// 	ray->dir_x = player->dir_x * cos(alpha) - player->dir_y * sin(alpha);
// 	ray->dir_y = player->dir_x * sin(alpha) + player->dir_y * cos(alpha);
// 	ray->map_x = (int)player->pos_x;
// 	ray->map_y = (int)player->pos_y;
// 	ray->delta_dist_x = fabs(1 / ray->dir_x);
// 	ray->delta_dist_y = fabs(1 / ray->dir_y);
// 	ray->hit = 0;
// 	ray->step_x = 1 - 2 * (ray->dir_x < 0);
// 	if (ray->dir_x < 0)
// 		ray->side_dist_x = (player->pos_x - ray->map_x)
// 			* ray->delta_dist_x;
// 	else
// 		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
// 			* ray->delta_dist_x;
// 	ray->step_y = 1 - 2 * (ray->dir_y < 0);
// 	if (ray->dir_y < 0)
// 		ray->side_dist_y = (player->pos_y - ray->map_y)
// 			* ray->delta_dist_y;
// 	else
// 		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
// 			* ray->delta_dist_y;
// }
//
// void	render_fisheye(const t_win *win)
// {
// 	int		x;
// 	int		height;
// 	t_ray	ray;
//
// 	x = 0;
// 	height = HEIGHT / 2;
// 	while (x < WIDTH)
// 	{
// 		init_ray_fe(&ray, win->player, x);
// 		perform_dda(win, &ray);
// 		ray.line_height = (int)(height / ray.perp_wall_dist);
// 		ray.draw_start = -ray.line_height / 2 + HEIGHT / 2;
// 		if (ray.draw_start < 0)
// 			ray.draw_start = 0;
// 		ray.draw_end = ray.line_height / 2 + HEIGHT / 2;
// 		if (ray.draw_end >= HEIGHT)
// 			ray.draw_end = HEIGHT - 1;
// 		fill_floor_ceil(win, &ray, x);
// 		render_wall(win, &ray, x);
// 		x++;
// 	}
// }