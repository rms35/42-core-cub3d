/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 17:35:45 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_player(t_player *p, char *grid, int width, int total)
{
	int	i;

	i = 0;
	while (i < total && (grid[i] == '1' || grid[i] == '0'))
		i++;
	p->grid_pos = i;
	p->pos_x = (double)(i % width) + 0.5;
	p->pos_y = (double)(i / width) + 0.5;
	grid[i] = '0';
	p->dir_x = 0.0;
	p->dir_y = -1.0;
	p->camp_mod = 0.66;
	p->camp_x = 0.66;
	p->camp_y = 0.0;
	p->speed = 0.01;
	p->turn_speed = 0.01;
	p->cos_r = cos(p->turn_speed);
	p->sin_r = sin(p->turn_speed);
	p->cos_l = cos(-p->turn_speed);
	p->sin_l = sin(-p->turn_speed);
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

void	setup_mlx(t_win *win, t_img *img)
{
	win->mlxptr = mlx_init();
	if (!win->mlxptr)
		exit(1);
	img->line_len = 0;
	img->bpp = 4;
	win->winptr = mlx_new_window(win->mlxptr, WIDTH, HEIGHT, "cub3d");
	if (!win->winptr)
		(free(win->mlxptr), exit(1));
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
	load_tex(win, &win->tex[0], win->map->no_path);
	load_tex(win, &win->tex[1], win->map->so_path);
	load_tex(win, &win->tex[2], win->map->we_path);
	load_tex(win, &win->tex[3], win->map->ea_path);
	load_tex(win, &win->tex[4], "./textures/floor.xpm");
	load_tex(win, &win->tex[5], "./textures/ceiling.xpm");
}
