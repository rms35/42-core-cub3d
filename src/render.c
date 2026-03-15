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

#include "../includes/cub3d.h"

static void	draw_line(const t_win *win, const t_ray *ray, int x, int color)
{
	int	y;
	int	int_x;

	y = 0;
	int_x = x * 4;
	while (y < HEIGHT)
	{
		while (y < ray->draw_start)
		{
			*(unsigned int *)(win->img->addr + (y * win->img->line_len + int_x))
				= win->map->ceil_color;
			y++;
		}
		while (y < ray->draw_end)
		{
			*(unsigned int *)(win->img->addr + (y * win->img->line_len + int_x)) =
				color;
			y++;
		}
		while (y < HEIGHT)
		{
			*(unsigned int *)(win->img->addr + (y * win->img->line_len + int_x))
				= win->map->floor_color;
			y++;
		}
	}
}

static int	get_wall(const t_ray *ray)
{
	int	color;

	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			color = 0x00FF0000;
		else
			color = 0x0000FF00;
	}
	else
	{
		if (ray->dir_y > 0)
			color = 0x5F0000FF;
		else
			color = 0x00FFFF00;
	}
	return (color);
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
		init_ray(win, &ray, x);
		perform_dda(win, &ray);
		if (ray.perp_wall_dist < 0.1)
			ray.perp_wall_dist = 0.1;
		ray.line_height = (int)((double)height / ray.perp_wall_dist);
		ray.draw_start = -ray.line_height / 2 + HEIGHT / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = ray.line_height / 2 + HEIGHT / 2;
		if (ray.draw_end >= HEIGHT)
			ray.draw_end = HEIGHT - 1;
		draw_line(win, &ray, x, get_wall(&ray));
		x++;
	}
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