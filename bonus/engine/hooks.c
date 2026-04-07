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

#include "../../includes/cub3d_bonus.h"

int	mouse_hook(int x, int y, t_win *win)
{
	static int	first_call;

	if (!first_call)
	{
		mlx_mouse_hide(win->mlxptr, win->winptr);
		mlx_mouse_move(win->mlxptr, win->winptr, WIDTH / 2, HEIGHT / 2);
		first_call = 1;
		return (0);
	}
	if (x == WIDTH / 2 && y == HEIGHT / 2)
		return (0);
	win->player->m_delta_x += (x - WIDTH / 2);
	win->player->m_delta_y += (y - HEIGHT / 2);
	mlx_mouse_move(win->mlxptr, win->winptr, WIDTH / 2, HEIGHT / 2);
	return (1);
}

// TODO: Proper cleanup
int	close_win(t_win *win)
{
	int	i;
	int	j;

	if (win->sprites)
	{
		j = 0;
		while (win->sprites[0].tex && j < N_FIRES)
		{
			if (win->sprites[0].tex[j].img)
				mlx_destroy_image(win->mlxptr, win->sprites[0].tex[j].img);
			j++;
		}
		i = 0;
		while (i < N_SPRITES)
		{
			free(win->sprites[i].tex);
			i++;
		}
		free(win->sprites);
	}
	mlx_mouse_show(win->mlxptr, win->winptr);
	i = 0;
	while (i < N_TEX)
	{
		if (win->textures[i].img)
			mlx_destroy_image(win->mlxptr, win->textures[i].img);
		i++;
	}
	if (win->img && win->img->img)
		mlx_destroy_image(win->mlxptr, win->img->img);
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
		free(win->map);
	}
	free(win->z_buffer);
	free(win->sprite_dist);
	free(win->sprite_order);
	exit(win->exit_status);
}

