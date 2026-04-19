/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:56:33 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 16:44:47 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#define P1_FOV 1.7

int	main(int argc, char **argv)
{
	t_player	player;
	t_img		img;
	t_win		win;
	t_map		*map;

	ft_bzero(&win, sizeof(t_win));
	map = NULL;
	if (parse_map_file(&map, argc, argv))
		return (free_map(map), 1);
	init_player(&player, map, P1_FOV);
	win.player = &player;
	win.map = map;
	win.img = &img;
	setup_mlx(&win, win.img);
	if (init_textures(&win))
		return (close_win(&win), 1);
	render_frame(&win);
	mlx_put_image_to_window(win.mlxptr, win.winptr, img.img, 0, 0);
	mlx_loop_hook(win.mlxptr, game_loop, &win);
	mlx_loop(win.mlxptr);
	return (0);
}
