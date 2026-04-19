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

#include "../../includes/cub3d.h"

static void	get_dir(t_player *p, const char c)
{
	if (c == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
	}
	if (c == 'S')
	{
		p->dir_x = 0;
		p->dir_y = 1;
	}
	if (c == 'W')
	{
		p->dir_x = 1;
		p->dir_y = 0;
	}
	if (c == 'E')
	{
		p->dir_x = -1;
		p->dir_y = 0;
	}
}

static void	init_player_vars(t_player *p, const double fov)
{
	p->camp_x = -p->dir_y * (tan(fov / 2));
	p->camp_y = p->dir_x * (tan(fov / 2));
	p->speed = P1_SPEED;
	p->rot_speed = P1_TURNSP;
	p->cos_r = cos(p->rot_speed);
	p->sin_r = sin(p->rot_speed);
	p->cos_l = cos(-p->rot_speed);
	p->sin_l = sin(-p->rot_speed);
	p->fov = fov;
	p->dir_mag = sqrt(p->dir_x * p->dir_x + p->dir_y * p->dir_y);
	p->radius = P1_R;
}

void	init_player(t_player *p, const t_map *map, const double fov)
{
	int	i;
	int	total;

	i = 0;
	total = map->width * map->height;
	while (i < total && !ft_strchr(PLYR_DIR, map->grid[i]))
		i++;
	if (i == total)
	{
		write(2, "Error: No player found in map\n", 30);
		exit(1);
	}
	p->pos_x = (double)(i % map->width) + 0.5;
	p->pos_y = (double)(i / map->width) + 0.5;
	get_dir(p, map->grid[i]);
	map->grid[i] = '0';
	init_player_vars(p, fov);
}

static void	setup_img(t_win *win, t_img *img)
{
	img->img = mlx_new_image(win->mlxptr, WIDTH, HEIGHT);
	if (!img->img)
	{
		win->exit_status = EXIT_FAILURE;
		close_win(win);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	if (!img->addr)
	{
		win->exit_status = EXIT_FAILURE;
		close_win(win);
	}
	img->width = WIDTH;
	img->height = HEIGHT;
}

void	setup_mlx(t_win *win, t_img *img)
{
	win->exit_status = EXIT_SUCCESS;
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
	mlx_hook(win->winptr, EVENT_KEY_PRESS, MASK_KEY_PRESS, key_press, win);
	mlx_hook(win->winptr, EVENT_KEY_RELEASE, MASK_KEY_RELEASE,
		key_release, win);
	mlx_hook(win->winptr, EVENT_DESTROY_NOTIFY, 0, close_win, win);
	setup_img(win, img);
}
