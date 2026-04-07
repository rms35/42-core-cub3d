/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/07 19:41:53 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "../includes/cub3d.h"

int	close_win(const t_win *win)
{
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
}*/

#include "../includes/cub3d.h"

int	close_win(const t_win *win)
{
	// Destruye la ventana y la imagen
	if (win->winptr)
		mlx_destroy_window(win->mlxptr, win->winptr);
	if (win->img && win->img->img)
		mlx_destroy_image(win->mlxptr, win->img->img);

	// Diferencia Linux / Mac
#ifdef __linux__
	if (win->mlxptr)
	{
		mlx_destroy_display(win->mlxptr);
		free(win->mlxptr);
	}
#endif
	// Mac libera solo lo que haga falta (MLX lo gestiona internamente)

	// Libera mapa
	if (win->map)
	{
		free(win->map->grid);
		free(win->map);
	}

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