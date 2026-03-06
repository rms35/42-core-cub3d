/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/02 17:25:37 by rafael-m         ###   ########.fr       */
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

int	key_press(const int keysym, t_win *win)
{
	if (keysym == XK_Escape)
		close_win(win, EXIT_SUCCESS);
	if (keysym < 65536)
		win->keys[keysym] = 1;
	return (0);
}

int	key_release(const int keysym, t_win *win)
{
	if (keysym < 65536)
		win->keys[keysym] = 0;
	return (0);
}

int	game_loop(const t_win *win)
{
	int		render;
	double	old_speed;

	render = 0;
	old_speed = win->player->speed;
	if (win->keys[XK_Shift_L] || win->keys[XK_Shift_R])
		win->player->speed *= 2.0;
	if (win->keys[XK_w])
		render |= move_up(win->map->grid, win->map->width, win->player);
	if (win->keys[XK_s])
		render |= move_down(win->map->grid, win->map->width, win->player);
	if (win->keys[XK_a])
		render |= move_left(win->map->grid, win->map->width, win->player);
	if (win->keys[XK_d])
		render |= move_right(win->map->grid, win->map->width, win->player);
	if (win->keys[XK_Left])
		render |= rotate_left(win->player);
	if (win->keys[XK_Right])
		render |= rotate_right(win->player);
	win->player->speed = old_speed;
	if (render)
	{
		render_frame(win);
		mlx_put_image_to_window(win->mlxptr, win->winptr, win->img->img, 0, 0);
	}
	return (0);
}

void	check_map(const t_map *map)
{
	int	i;
	int	total;

	total = map->height * map->width;
	i = 0;
	while (i < total)
	{
		printf("%c ", map->grid[i]);
		if (i != 0 && (i + 1) % map->width == 0)
			printf("\n");
		i++;
	}
	write(1, "\n", 1);
}

void	init_player(t_player *player, char *grid, const int width, const int total)
{
	int	i;

	i = 0;
	while (i < total && (grid[i] == '1' || grid[i] == '0'))
		i++;
	player->grid_pos = i;
	player->pos_x = (double)(i % width) + 0.5;
	player->pos_y = (double)(i / width) + 0.5;
	grid[i] = '0';
	player->dir_x = 0.0;
	player->dir_y = 1.0;
	player->camp_mod = 0.66;
	player->camp_x = -0.66;
	player->camp_y = 0.0;
	player->speed = 0.01;
	player->turn_speed = 0.0075;
	player->cos_r = cos(player->turn_speed);
	player->sin_r = sin(player->turn_speed);
	player->cos_l = cos(-player->turn_speed);
	player->sin_l = sin(-player->turn_speed);
}

int	main(void)
{
	t_win		win;
	t_img		img;
	t_map		*map;
	t_player	player;

	ft_memset(&win, 0, sizeof(t_win));
	map = get_mock_map();
	win.map = map;
	win.img = &img;
	win.player = &player;
	init_player(&player, map->grid, map->width, map->width * map->height);
	win.mlxptr = mlx_init();
	if (!win.mlxptr)
		return (1);
	img.line_len = 0;
	img.bpp = 4;
	win.winptr = mlx_new_window(win.mlxptr, WIDTH, HEIGHT, "cub3d");
	if (!win.winptr)
		return (free(win.mlxptr), 1);
	mlx_hook(win.winptr, KeyPress, KeyPressMask, key_press, &win);
	mlx_hook(win.winptr, KeyRelease, KeyReleaseMask, key_release, &win);
	mlx_hook(win.winptr, DestroyNotify, 0, close_win, &win);
	img.img = mlx_new_image(win.mlxptr, WIDTH, HEIGHT);
	if (!img.img)
		return (write(2, "!Error img\n", 11), close_win(&win, EXIT_FAILURE), 1);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	if (!img.addr)
		return (write(2, "Error addr\n", 12), free(img.img), close_win(&win, EXIT_FAILURE), 1);
	render_frame(&win);
	mlx_put_image_to_window(win.mlxptr, win.winptr, img.img, 0, 0);
	mlx_loop_hook(win.mlxptr, game_loop, &win);
	mlx_loop(win.mlxptr);
	return (0);
}