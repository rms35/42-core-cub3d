/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 17:10:00 by rafael           ###   ########.fr       */
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
	p->dir_y = 1.0;
	p->camp_mod = 0.66;
	p->camp_x = -0.66;
	p->camp_y = 0.0;
	p->speed = 0.01;
	p->turn_speed = 0.0075;
	p->cos_r = cos(p->turn_speed);
	p->sin_r = sin(p->turn_speed);
	p->cos_l = cos(-p->turn_speed);
	p->sin_l = sin(-p->turn_speed);
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
