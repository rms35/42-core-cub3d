/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_door2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 20:56:17 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	get_door_wall_x(const t_win *win, t_ray *ray)
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

static int	door_dda_hit(const t_win *win, t_ray *ray, const t_sprite *door)
{
	if (win->map->grid[ray->map_y * win->map->width + ray->map_x] == 'D'
		&& ray->map_x == (int)door->x && ray->map_y == (int)door->y)
	{
		if (ray->side == 0)
		{
			ray->perp_dist = ray->side_dist_x - 0.5 * ray->delta_dist_x;
			if (floor(win->player->pos_y + ray->perp_dist * ray->dir_y)
				== ray->map_y)
				return (1);
		}
		else
		{
			ray->perp_dist = ray->side_dist_y - 0.5 * ray->delta_dist_y;
			if (floor(win->player->pos_x + ray->perp_dist * ray->dir_x)
				== ray->map_x)
				return (1);
		}
	}
	return (0);
}

int	door_dda(t_win *win, t_ray *ray, const t_sprite *door)
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
		if (ft_strchr(WALLS, win->map->grid[ray->map_y * win->map->width +
			ray->map_x]))
			return (1);
		if (door_dda_hit(win, ray, door))
			ray->hit = 1;
	}
	get_door_wall_x(win, ray);
	return (0);
}
