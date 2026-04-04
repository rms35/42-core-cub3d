/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/02 14:30:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

#define P1_FOV 1.7

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
		if (win->player->pitch > 400)
			win->player->pitch = 400;
		if (win->player->pitch < -400)
			win->player->pitch = -400;
		win->player->m_delta_y = 0;
	}
	render_frame(win);
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
	ft_bzero(&win, sizeof(t_win));
	win.z_buffer = ft_calloc(WIDTH, sizeof(double));
	if (!win.z_buffer)
	{
		write(2, "Error: malloc\n", 8);
		return (1);
	}
	win.keys = keys;
	win.player = &player;
	win.map = map;
	win.img = &img;
	init_player(&player, map, P1_FOV);
	setup_mlx(&win, &img);
	if (init_textures(&win) || init_sprites(&win, map))
		return (1);
	mlx_loop_hook(win.mlxptr, game_loop, &win);
	mlx_loop(win.mlxptr);
	return (0);
}
