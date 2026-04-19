/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/08 16:20:31 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

#ifdef LINUX

static void	destroy_display(const t_win *win)
{
	if (win->mlxptr)
	{
		mlx_destroy_display(win->mlxptr);
		free(win->mlxptr);
	}
}

#else

static void	destroy_display(const t_win *win)
{
	(void)win;
}

#endif

int	close_win(const t_win *win)
{
	int	i;

	if (win->winptr)
		mlx_destroy_window(win->mlxptr, win->winptr);
	if (win->img && win->img->img)
		mlx_destroy_image(win->mlxptr, win->img->img);
	i = 0;
	while (i < N_TEX)
	{
		if (win->textures[i].img)
			mlx_destroy_image(win->mlxptr, win->textures[i].img);
		i++;
	}
	destroy_display(win);
	if (win->map)
		free_map(win->map);
	exit(win->exit_status);
}

int	game_loop(const t_win *win)
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
