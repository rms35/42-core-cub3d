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

#include "../includes/cub3d.h"

static void	free_tex(const t_win *win)
{
	int	i;

	i = 0;
	while (i < 6)
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
		free(win->map->no_path);
		free(win->map->so_path);
		free(win->map->we_path);
		free(win->map->ea_path);
		free(win->map->sky_path);
		free(win->map);
	}
	exit(win->exit_status);
}

int	game_loop(t_win *win)
{
	win->pulse_time += 0.05;
	handle_input(win);
	render_frame(win);
	mlx_put_image_to_window(win->mlxptr, win->winptr, win->img->img, 0, 0);
	return (0);
}
