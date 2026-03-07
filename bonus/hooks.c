/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 18:55:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

static void	free_tex(const t_win *win)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (win->tex[i].img)
			mlx_destroy_image(win->mlxptr, win->tex[i].img);
		i++;
	}
	if (win->sky_tex.img)
		mlx_destroy_image(win->mlxptr, win->sky_tex.img);
}

int	close_win(t_win *win)
{
	if (win->winptr)
		mlx_destroy_window(win->mlxptr, win->winptr);
	free_tex(win);
	if (win->img->img)
		mlx_destroy_image(win->mlxptr, win->img->img);
	if (win->accum->img)
		mlx_destroy_image(win->mlxptr, win->accum->img);
	if (win->mlxptr)
	{
		mlx_destroy_display(win->mlxptr);
		free(win->mlxptr);
	}
	if (win->map)
	{
		free(win->map->grid);
		free(win->map->door_state);
		free(win->map->door_target);
		free(win->map->no_path);
		free(win->map->so_path);
		free(win->map->we_path);
		free(win->map->ea_path);
		free(win->map->sky_path);
		free(win->map);
	}
	exit(win->exit_status);
}

static void	update_doors(t_win *win)
{
	int	i;
	int	total;

	total = win->map->width * win->map->height;
	i = 0;
	while (i < total)
	{
		if (win->map->door_state[i] < win->map->door_target[i])
		{
			win->map->door_state[i] += 0.02;
			if (win->map->door_state[i] > win->map->door_target[i])
				win->map->door_state[i] = win->map->door_target[i];
		}
		else if (win->map->door_state[i] > win->map->door_target[i])
		{
			win->map->door_state[i] -= 0.02;
			if (win->map->door_state[i] < win->map->door_target[i])
				win->map->door_state[i] = win->map->door_target[i];
		}
		i++;
	}
}

int	game_loop(t_win *win)
{
	double	jump_z;
	double	bob_z;

	win->pulse_time += 0.05;
	update_doors(win);
	jump_z = 0;
	bob_z = 0;
	if (win->player->jump_t >= 0)
	{
		win->player->jump_t += 0.1;
		jump_z = sin(win->player->jump_t) * 0.5;
		if (win->player->jump_t >= M_PI)
			win->player->jump_t = -1.0;
	}
	else
		bob_z = sin(win->player->walk_t * 1.5) * 0.02;
	win->player->pos_z = jump_z + bob_z;
	handle_input(win);
	render_frame(win);
	mlx_put_image_to_window(win->mlxptr, win->winptr, win->img->img, 0, 0);
	return (0);
}
