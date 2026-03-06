/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:56:33 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 17:00:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	fill_column(const t_win *win, t_ray *ray, int x, int color)
{
	int		y;
	char	*dst;

	dst = win->img->addr + (x * (win->img->bpp / 8));
	y = 0;
	while (y < ray->draw_start)
	{
		*(unsigned int *)dst = win->map->ceil_color;
		dst += win->img->line_len;
		y++;
	}
	while (y <= ray->draw_end)
	{
		*(unsigned int *)dst = color;
		dst += win->img->line_len;
		y++;
	}
	while (y < HEIGHT)
	{
		*(unsigned int *)dst = win->map->floor_color;
		dst += win->img->line_len;
		y++;
	}
}

static void	init_ray(const t_win *win, t_ray *ray, const int x)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = win->player->dir_x + win->player->camp_x * camera_x;
	ray->dir_y = win->player->dir_y + win->player->camp_y * camera_x;
	ray->map_x = (int)win->player->pos_x;
	ray->map_y = (int)win->player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
	ray->step_x = 1 - 2 * (ray->dir_x < 0);
	if (ray->dir_x < 0)
		ray->side_dist_x = (win->player->pos_x - ray->map_x)
			* ray->delta_dist_x;
	else
		ray->side_dist_x = (ray->map_x + 1.0 - win->player->pos_x)
			* ray->delta_dist_x;
	ray->step_y = 1 - 2 * (ray->dir_y < 0);
	if (ray->dir_y < 0)
		ray->side_dist_y = (win->player->pos_y - ray->map_y)
			* ray->delta_dist_y;
	else
		ray->side_dist_y = (ray->map_y + 1.0 - win->player->pos_y)
			* ray->delta_dist_y;
}

static void	perform_dda(const t_win *win, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (win->map->grid[ray->map_y * win->map->width + ray->map_x] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
}

static void	draw_vertical_line(const t_win *win, t_ray *ray, int x)
{
	int	color;

	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (ray->side == 1)
		color = 0x555555;
	else
		color = 0xAAAAAA;
	fill_column(win, ray, x, color);
}

void	render_frame(const t_win *win)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(win, &ray, x);
		perform_dda(win, &ray);
		draw_vertical_line(win, &ray, x);
		x++;
	}
}
