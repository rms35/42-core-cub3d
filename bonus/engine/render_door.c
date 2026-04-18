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

#include "../../includes/cub3d_bonus.h"

static void init_for_dda(const t_win *win, t_ray *ray)
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

int	door_dda(const t_win *win, t_ray *ray)
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
			return (1);
		if (win->map->grid[ray->map_y * win->map->width + ray->map_x] == 'D')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_dist = (ray->map_x - win->player->pos_x + (1 -
			ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_dist = (ray->map_y - win->player->pos_y + (1 -
			ray->step_y) / 2) / ray->dir_y;
	get_wall_x(win, ray);
	return (0);
}


static void	draw_door(const t_win *win, t_ray *ray, const int int_x, int y)
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

	y = ray->draw_start;
	offset = x * (win->img->bpp / 8);
	while (y < ray->draw_end)
	{
		draw_door(win, ray, offset, y);
		y++;
	}
}

void	render_door(const t_win *win, const t_sprite *door)
{
	t_ray	ray;
	int		x;
	int		center_ofs;

	x = 0;
	ray.tex = win->door;
	while (x < WIDTH)
	{
		init_for_dda(win, &ray);
		init_ray(win, &ray, x);
		if (door_dda(win, &ray))
		{
			x++;
			continue ;
		}
		if (ray.perp_dist < 0.1)
			ray.perp_dist = 0.1;
		win->z_buffer[x] = ray.perp_dist;
		center_ofs = (HEIGHT / 2) + win->player->pitch;
		ray.line_height = (int)((double)HEIGHT / ray.perp_dist);
		ray.draw_start = center_ofs - (ray.line_height / 2);
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = center_ofs + (ray.line_height/ 2);
		if (ray.draw_end >= HEIGHT)
			ray.draw_end = HEIGHT - 1;
		ray.tex_step = 1.0 * door->tex->height / ray.line_height;
		ray.tex_pos = (ray.draw_start - center_ofs + ray.line_height / 2) *
			ray.tex_step;
		draw_line(win, &ray, x);
		x++;
	}
}