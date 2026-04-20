/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 16:25:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

double	get_time(void)
{
	struct timespec	t;

	clock_gettime(CLOCK_MONOTONIC, &t);
	return (t.tv_sec + t.tv_nsec / 1e9);
}

int	mouse_hook(int x, int y, void *param)
{
	t_win		*win;
	static int	first_call;
	int			delta_x;
	int			delta_y;

	win = (t_win *)param;
	if (!first_call)
	{
		mlx_mouse_hide(win->mlxptr, win->winptr);
		mlx_mouse_move(win->mlxptr, win->winptr, WIDTH / 2, HEIGHT / 2);
		first_call = 1;
		return (0);
	}
	if (x == WIDTH / 2 && y == HEIGHT / 2)
		return (0);
	delta_x = x - (WIDTH / 2);
	delta_y = y - (HEIGHT / 2);
	win->player->m_delta_x += delta_x;
	win->player->m_delta_y += delta_y;
	mlx_mouse_move(win->mlxptr, win->winptr, WIDTH / 2, HEIGHT / 2);
	return (1);
}

int	close_win(void *param)
{
	t_win	*win;

	win = (t_win *)param;
	cleanup_textures(win);
	free(win->sprites);
	cleanup_mlx(win);
	if (win->map)
	{
		free(win->map->no_path);
		free(win->map->so_path);
		free(win->map->we_path);
		free(win->map->ea_path);
		free(win->map->grid);
		free(win->map);
	}
	free(win->z_buffer);
	free(win->pairs);
	free(win->sprite_dist);
	free(win->sprite_order);
	exit(win->exit_status);
	return (0);
}
