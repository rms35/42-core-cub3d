/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 12:00:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

#define P1_FOV 1.7

static void	init_minimap_lookup(t_win *win)
{
	win->minilu['1'] = 0x00AAAAAA;
	win->minilu['0'] = 0x00000000;
	win->minilu[256] = 0x00FF0000;
	win->minilu['D'] = 0x00FFFFFF;
	win->minilu['F'] = 0x00FFBB00;
}

static int	game_loop(void *param)
{
	t_win	*win;
	double	now;

	win = (t_win *)param;
	now = get_time();
	win->delta_time = now - win->last_frame;
	win->last_frame = now;
	handle_input(win);
	handle_mouse_rotation(win);
	render_frame(win);
	mlx_put_image_to_window(win->mlxptr, win->winptr, win->img->img, 0, 0);
	return (0);
}

void	init_window_state(t_win *win, t_player *player, t_img *img, int
	*keys)
{
	win->keys = keys;
	win->player = player;
	win->img = img;
	init_minimap_lookup(win);
}

static int	start_rendering_loop(t_win *win, t_map *map)
{
	init_player(win->player, map, P1_FOV);
	setup_mlx(win, win->img);
	if (init_textures(win) || init_sprites(win, map))
		return (1);
	mlx_loop_hook(win->mlxptr, (void *)game_loop, win);
	mlx_loop(win->mlxptr);
	return (0);
}

int	main(int argc, char **argv)
{
	t_player	player;
	t_img		img;
	t_win		win;
	t_map		*map;
	static int	keys[N_KEYS];

	map = parsing(argc, argv);
	if (!map)
		return (1);
	ft_bzero(&win, sizeof(t_win));
	win.z_buffer = ft_calloc(WIDTH, sizeof(double));
	if (!win.z_buffer)
	{
		write(2, "Error: malloc\n", 8);
		return (1);
	}
	init_window_state(&win, &player, &img, keys);
	win.map = map;
	if (start_rendering_loop(&win, map))
		return (1);
	return (0);
}
