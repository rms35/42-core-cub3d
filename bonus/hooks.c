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

#include "../includes/cub3d_bonus.h"

int	mouse_hook(const int x, const int y, const t_win *win)
{
	if (x == WIDTH / 2 && y == HEIGHT / 2)
		return (0);
	win->player->m_delta_x += (x - WIDTH / 2);
	win->player->m_delta_y += (y - HEIGHT / 2);
	mlx_mouse_move(win->mlxptr, win->winptr, WIDTH / 2, HEIGHT / 2);
	return (1);
}

// TODO: Free sprite's related data
int	close_win(const t_win *win)
{
	int	i;

	mlx_mouse_show(win->mlxptr, win->winptr);
	i = 0;
	while (i < N_TEX)
	{
		mlx_destroy_image(win->mlxptr, win->textures[i].img);
		i++;
	}
	i = 0;
	while (i < N_SPRITES)
	{
		mlx_destroy_image(win->mlxptr, win->sprites->tex.img);
		i++;
	}
	if (win->winptr)
		mlx_destroy_window(win->mlxptr, win->winptr);
	if (win->img->img)
		mlx_destroy_image(win->mlxptr, win->img->img);
	if (win->mlxptr)
	{
		mlx_destroy_display(win->mlxptr);
		free(win->mlxptr);
	}
	if (win->map)
	{
		free(win->map->grid);
		free(win->map);
	}
	free(win->z_buffer);
	free(win->sprite_dist);
	free(win->sprite_order);
	free(win->sprites);
	exit(win->exit_status);
}
