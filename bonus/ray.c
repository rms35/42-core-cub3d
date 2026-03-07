/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:15:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/07 18:40:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	init_ray(const t_win *win, t_ray *ray, const int x)
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
	ray->is_door = 0;
	ray->is_frame = 0;
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

void	perform_dda(const t_win *win, t_ray *ray)
{
	char	cell;
	double	d_dist;
	double	hit_val;
	int		prev_x;
	int		prev_y;
	double	state;

	while (ray->hit == 0)
	{
		prev_x = ray->map_x;
		prev_y = ray->map_y;
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
		cell = win->map->grid[ray->map_y * win->map->width + ray->map_x];
		if (cell == '1')
		{
			ray->hit = 1;
			if (win->map->grid[prev_y * win->map->width + prev_x] == 'D')
				ray->is_frame = 1;
		}
		else if (cell == 'D')
		{
			if (ray->side == 0)
				d_dist = ray->side_dist_x - ray->delta_dist_x / 2;
			else
				d_dist = ray->side_dist_y - ray->delta_dist_y / 2;
			if (ray->side == 0 && d_dist >= ray->side_dist_y)
				continue ;
			if (ray->side == 1 && d_dist >= ray->side_dist_x)
				continue ;
			if (ray->side == 0)
				hit_val = win->player->pos_y + d_dist * ray->dir_y;
			else
				hit_val = win->player->pos_x + d_dist * ray->dir_x;
			hit_val -= floor(hit_val);
			state = win->map->door_state[ray->map_y * win->map->width + ray->map_x] / 2.0;
			if (hit_val < 0.5 - state || hit_val > 0.5 + state)
			{
				ray->hit = 1;
				ray->is_door = 1;
				ray->perp_wall_dist = d_dist;
			}
		}
	}
	if (ray->is_door == 0)
	{
		if (ray->side == 0)
			ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
		else
			ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	}
}
