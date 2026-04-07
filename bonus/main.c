/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 18:30:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

#define P1_FOV 1.7

void print_grid(const char *grid, size_t width, size_t height)
{
	size_t	i;

	i = 0;
	while (i < width * height)
	{
		write(1, grid + i, width);
		i += width;
	}
}

static int	game_loop(t_win *win)
{
	double now;

	now = get_time();
	win->delta_time = now - win->last_frame;
	win->last_frame = now;
	handle_input(win);
	if (win->player->m_delta_x != 0)
	{
		rot_x_axis(win->player, (double)win->player->m_delta_x * M_SENS);
		win->player->m_delta_x = 0;
	}
	if (win->player->m_delta_y != 0)
	{
		win->player->pitch -= win->player->m_delta_y;
		win->player->m_delta_y = 0;
		if (win->player->pitch > HEIGHT / 2)
			win->player->pitch = HEIGHT / 2;
		if (win->player->pitch < -HEIGHT / 2)
			win->player->pitch = -HEIGHT / 2;
	}
	render_frame(win);
	animate_sprites(&win->sprites[0], now * 1000);
	mlx_put_image_to_window(win->mlxptr, win->winptr, win->img->img, 0, 0);
	now = get_time();
	if (now - win->last_frame < (double)FRAME_DELAY / 1000.0)
		usleep(((double)FRAME_DELAY / 1000.0 - (now - win->last_frame)) * 1e6);
	return (0);
}


int	main(int argc, char **argv)
{
	t_player	player;
	t_img		img;
	t_win		win;
	t_map		*map;
	static int	keys[N_KEYS];

	map = parsing(argc, argv[1]);
	if (!map)
		return (1);
	print_grid(map->grid, map->width, map->height);
	free(map->grid);
	free(map);
	return (0);
	ft_bzero(&win, sizeof(t_win));
	win.z_buffer = ft_calloc(WIDTH, sizeof(double));
	if (!win.z_buffer)
	{
		write(2, "Error: malloc\n", 8);
		exit(EXIT_FAILURE);
	}
	win.img = &img;
	win.keys = keys;
	win.player = &player;
	setup_mlx(&win, win.img);
	map = get_mock_map(&win);
	init_player(&player, map, P1_FOV);
	init_sprites(&win, map);
	win.map = map;
	win.last_frame = get_time();
	mlx_loop_hook(win.mlxptr, game_loop, &win);
	mlx_loop(win.mlxptr);
	return (0);
}
