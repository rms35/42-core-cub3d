/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 17:10:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	main(void)
{
	t_win		win;
	t_img		img;
	t_img		accum;
	t_player	player;

	int			i;

	ft_memset(&win, 0, sizeof(t_win));
	ft_memset(&img, 0, sizeof(t_img));
	ft_memset(&accum, 0, sizeof(t_img));
	ft_memset(&win.sky_tex, 0, sizeof(t_img));
	i = -1;
	while (++i < 10)
		ft_memset(&win.tex[i], 0, sizeof(t_img));
	win.map = get_mock_map();
	win.img = &img;
	win.accum = &accum;
	win.player = &player;
	if (!win.map)
		return (1);
	init_player(&player, win.map->grid, win.map->width,
		win.map->width * win.map->height);
	setup_mlx(&win, &img);
	render_frame(&win);
	mlx_put_image_to_window(win.mlxptr, win.winptr, img.img, 0, 0);
	mlx_loop_hook(win.mlxptr, game_loop, &win);
	mlx_loop(win.mlxptr);
	return (0);
}
