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

/* TODO:	NOW
*		 - sprites
*		 - minimap
*		 -
*			LATER:
*		 - Head bobbing
*		 - Mouse physics
*		 - Sky/ceiling and floor textures
*		 - Planned map nad textures
*		 - Jumping and crouching
*		 - Nice HUD
*		 - Different players/modes for the same player
*		 - FOV variation when running?
*/

int	game_loop(const t_win *win)
{
	int	render;

	render = handle_input(win);
	if (win->player->m_delta_x != 0)
	{
		rot_x_axis(win->player, (double)win->player->m_delta_x * M_SENS);
		win->player->m_delta_x = 0;
		render = 1;
	}
	if (win->player->m_delta_y != 0)
	{
		win->player->pitch -= win->player->m_delta_y;
		win->player->m_delta_y = 0;
		if (win->player->pitch > HEIGHT / 2)
			win->player->pitch = HEIGHT / 2;
		if (win->player->pitch < -HEIGHT / 2)
			win->player->pitch = -HEIGHT / 2;
		render = 1;
	}
	if (render)
	{
		render_frame(win);
		mlx_put_image_to_window(win->mlxptr, win->winptr, win->img->img, 0, 0);
	}
	return (0);
}

int	main(void)
{
	t_player	player;
	t_img		img;
	t_win		win;
	t_map		*map;
	static int	keys[N_KEYS];

	ft_bzero(&win, sizeof(t_win));
	win.img = &img;
	win.keys = keys;
	setup_mlx(&win, win.img);
	map = get_mock_map(&win);
	init_player(&player, map, P1_FOV);
	win.player = &player;
	win.map = map;
	render_frame(&win);
	mlx_put_image_to_window(win.mlxptr, win.winptr, img.img, 0, 0);
	mlx_loop_hook(win.mlxptr, game_loop, &win);
	mlx_loop(win.mlxptr);
	return (0);
}
