/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 17:00:00 by rafael           ###   ########.fr       */
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

static int	handle_input(const t_win *win)
{
	int	r;

	r = 0;
	if (win->keys[XK_w])
		r |= move_up(win->map->grid, win->map->width, win->player);
	if (win->keys[XK_s])
		r |= move_down(win->map->grid, win->map->width, win->player);
	if (win->keys[XK_a])
		r |= move_left(win->map->grid, win->map->width, win->player);
	if (win->keys[XK_d])
		r |= move_right(win->map->grid, win->map->width, win->player);
	if (win->keys[XK_Left])
		r |= rotate_left(win->player);
	if (win->keys[XK_Right])
		r |= rotate_right(win->player);
	return (r);
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

static void	setup_mlx(t_win *win, t_img *img)
{
	win->mlxptr = mlx_init();
	if (!win->mlxptr)
		exit(1);
	img->line_len = 0;
	img->bpp = 4;
	win->winptr = mlx_new_window(win->mlxptr, WIDTH, HEIGHT, "cub3d");
	if (!win->winptr)
	{
		free(win->mlxptr);
		exit(1);
	}
	mlx_hook(win->winptr, KeyPress, KeyPressMask, key_press, win);
	mlx_hook(win->winptr, KeyRelease, KeyReleaseMask, key_release, win);
	mlx_hook(win->winptr, DestroyNotify, 0, close_win, win);
	img->img = mlx_new_image(win->mlxptr, WIDTH, HEIGHT);
	if (!img->img)
		close_win(win, EXIT_FAILURE);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
		close_win(win, EXIT_FAILURE);
}

int	main(void)
{
	t_win		win;
	t_img		img;
	t_player	player;

	ft_memset(&win, 0, sizeof(t_win));
	win.map = get_mock_map();
	win.img = &img;
	win.player = &player;
	init_player(&player, win.map->grid, win.map->width,
		win.map->width * win.map->height);
	setup_mlx(&win, &img);
	render_frame(&win);
	mlx_put_image_to_window(win.mlxptr, win.winptr, img.img, 0, 0);
	mlx_loop_hook(win.mlxptr, game_loop, &win);
	mlx_loop(win.mlxptr);
	return (0);
}
