/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 20:00:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_player *p, char *grid, int width, int total)
{
	int	i;

	i = 0;
	while (i < total && (grid[i] == '1' || grid[i] == '0'))
		i++;
	p->pos_x = (double)(i % width) + 0.5;
	p->pos_y = (double)(i / width) + 0.5;
	grid[i] = '0';
	p->dir_x = 0.0;
	p->dir_y = -1.0;
	p->camp_x = 0.66;
	p->camp_y = 0.0;
	p->speed = 0.03;
	p->turn_speed = 0.0005;
	p->cos_r = cos(p->turn_speed);
	p->sin_r = sin(p->turn_speed);
	p->cos_l = cos(-p->turn_speed);
	p->sin_l = sin(-p->turn_speed);
	p->pitch = 0;
}

static void	load_tex(t_win *win, t_img *tex, char *path)
{
	int	w;
	int	h;

	tex->img = mlx_xpm_file_to_image(win->mlxptr, path, &w, &h);
	if (!tex->img)
	{
		write(2, "Error loading texture\n", 22);
		close_win(win, EXIT_FAILURE);
	}
	tex->addr = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len,
			&tex->endian);
}

static void	setup_buffers(t_win *win, t_img *img)
{
	img->img = mlx_new_image(win->mlxptr, WIDTH, HEIGHT);
	if (!img->img)
		close_win(win, EXIT_FAILURE);
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
		close_win(win, EXIT_FAILURE);
	win->accum->img = mlx_new_image(win->mlxptr, WIDTH, HEIGHT);
	if (!win->accum->img)
		close_win(win, EXIT_FAILURE);
	win->accum->addr = mlx_get_data_addr(win->accum->img, &win->accum->bpp,
			&win->accum->line_len, &win->accum->endian);
	if (!win->accum->addr)
		close_win(win, EXIT_FAILURE);
}

static void	load_all_tex(t_win *win)
{
	load_tex(win, &win->tex[0], win->map->no_path);
	load_tex(win, &win->tex[1], win->map->so_path);
	load_tex(win, &win->tex[2], win->map->we_path);
	load_tex(win, &win->tex[3], win->map->ea_path);
	load_tex(win, &win->tex[4], "./textures/floor.xpm");
	load_tex(win, &win->tex[5], "./textures/ceiling.xpm");
}

void	setup_mlx(t_win *win, t_img *img)
{
	win->mlxptr = mlx_init();
	if (!win->mlxptr)
		exit(1);
	img->line_len = 0;
	img->bpp = 4;
	win->accum->line_len = 0;
	win->accum->bpp = 4;
	win->winptr = mlx_new_window(win->mlxptr, WIDTH, HEIGHT, "cub3d");
	if (!win->winptr)
		(free(win->mlxptr), exit(1));
	mlx_hook(win->winptr, KeyPress, KeyPressMask, key_press, win);
	mlx_hook(win->winptr, KeyRelease, KeyReleaseMask, key_release, win);
	mlx_hook(win->winptr, MotionNotify, PointerMotionMask, mouse_move, win);
	mlx_hook(win->winptr, DestroyNotify, 0, close_win, win);
	setup_buffers(win, img);
	win->pulse_time = 0.0;
	win->mouse_x = WIDTH / 2;
	win->mouse_y = HEIGHT / 2;
	load_all_tex(win);
	mlx_mouse_hide(win->mlxptr, win->winptr);
}
