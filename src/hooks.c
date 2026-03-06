/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 17:10:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_win(const t_win *win, const int keysym)
{
	if (win->winptr)
		mlx_destroy_window(win->mlxptr, win->winptr);
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
		free(win->map);
	}
	exit(keysym);
}

int	game_loop(const t_win *win)
{
	int		render;
	double	old_speed;

	render = 0;
	old_speed = win->player->speed;
	if (win->keys[XK_Shift_L] || win->keys[XK_Shift_R])
		win->player->speed *= 2.5;
	render = handle_input(win);
	win->player->speed = old_speed;
	if (render)
	{
		render_frame(win);
		mlx_put_image_to_window(win->mlxptr, win->winptr, win->img->img, 0, 0);
	}
	return (0);
}
