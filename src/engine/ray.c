/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:15:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 17:15:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static void	init_for_dda(const t_win *win, t_ray *ray)
{
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

static void	get_wall_x(const t_win *win, t_ray *ray)
{
	if (ray->side == 0)
		ray->wall_x = win->player->pos_y + ray->perp_dist * ray->dir_y;
	else
		ray->wall_x = win->player->pos_x + ray->perp_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->wall_x = 1.0 - ray->wall_x;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->wall_x = 1.0 - ray->wall_x;
}

void	init_ray(const t_win *win, t_ray *ray, const int x)
{
	double	cam_x;

	cam_x = 2 * x / (double)WIDTH - 1;
	ray->dir_x = win->player->dir_x + win->player->camp_x * cam_x;
	ray->dir_y = win->player->dir_y + win->player->camp_y * cam_x;
	ray->map_x = (int)win->player->pos_x;
	ray->map_y = (int)win->player->pos_y;
	init_for_dda(win, ray);
}

void	perform_dda(const t_win *win, t_ray *ray)
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
		ray->perp_dist = (ray->map_x - win->player->pos_x + (1 - ray->step_x)
				/ 2) / ray->dir_x;
	else
		ray->perp_dist = (ray->map_y - win->player->pos_y + (1
					- ray->step_y) / 2) / ray->dir_y;
	get_wall_x(win, ray);
}
