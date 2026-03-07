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
}

int	close_win(const t_win *win, const int status)
{
	if (win->winptr)
		mlx_destroy_window(win->mlxptr, win->winptr);
	free_tex(win);
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
	exit(status);
}

int	game_loop(t_win *win)
{
	int		render;

	render = handle_input(win);
	if (render)
	{
		render_frame(win);
		mlx_put_image_to_window(win->mlxptr, win->winptr, win->img->img, 0, 0);
	}
	return (0);
}
