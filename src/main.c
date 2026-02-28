/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_win(const t_win *win, const int keysym)
{

	if (win->winptr)
		mlx_destroy_window(win->mlxptr, win->winptr);
	if (win->mlxptr)
	{
		mlx_destroy_display(win->mlxptr);
		free(win->mlxptr);
	}
	if (win->map)
	{
		free(win->map->grid);
		free(win->map->no_path);
		free(win->map->so_path);
		free(win->map->we_path);
		free(win->map->ea_path);
		free(win->map);
	}
	exit(keysym);
}

int handle_keypress(const int keysym, void *data)
{
	const t_win *win = (t_win *)data;
	int	render;

	render = 0;
	if (keysym == XK_Escape)
		close_win(win, EXIT_SUCCESS);
	if (keysym == XK_w)
		render = move_up(win->map);
	if (keysym == XK_a)
		render = move_left(win->map);
	if (keysym == XK_s)
		render = move_down(win->map);
	if (keysym == XK_d)
		render = move_right(win->map);
	if (render)
	{
		twod_map(win->map, win->img);
		mlx_put_image_to_window(win->mlxptr, win->winptr, win->img->img, 0, 0);
	}
	return (0);
}

void	init_data(t_win *win)
{
	win->mlxptr = NULL;
	win->winptr = NULL;
}

void	my_mlx_pixel_put(const t_img *img, const int x, const int y, const int
	color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void	set_cell(const t_img *img, const int x, const int y, const int color)
{
	int	i;
	int	j;

	// printf("x2 = %d; y2 = %d\n", x, y);
	i = 0;
	while (i < FACTOR)
	{
		j = 0;
		while (j < FACTOR)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i ++;
	}
}

void	twod_map(const t_map *map, const t_img *img)
{
		int	x;
		int	y;
		int	total;

		total = map->width * map ->height;
		x = 0;
		while (x < total)
		{
			y = 0;
			while (y < map->height)
			{
				// printf("x = %d; y = %d;x + y = %d; char = %c\n",x, y, x + y,
					// map->grid[x + y]);
				if (map->grid[x + y] == '1')
					set_cell(img,y * FACTOR, (x / map->width) * FACTOR,
						0x000000FF);
				if (map->grid[x + y] == 'N')
					set_cell(img, y * FACTOR, (x / map->width) * FACTOR, 0x00FF0000);
				if (map->grid[x + y] == '0')
					set_cell(img, y * FACTOR, (x / map->width) * FACTOR, 0x00F00FF00);
				y++;
			}
			// printf("\n");
			x += map->width;
		}
}

void init_player(t_player *p)
{
	p->pos_x = 2.0;
	p->pos_y = 1.0;
	p->dir_x = 0.0;
	p->dir_y = 1.0;
	p->camp_mod = 0.66;
	p->camp_x = 0.0;
	p->camp_y = p->camp_mod;
}

void	check_map(const t_map *map)
{
	int	i;
	int	total;

	total = map->height * map->width;
	i = 0;
	while (i < total)
	{
		printf("%c ", map->grid[i]);
		if (i != 0 && (i + 1) % map->width == 0)
			printf("\n");
		i++;
	}
	write(1, "\n", 1);
}

int	main(void)
{
	t_win	win;
	t_img	img;
	t_map	*map;

	init_data(&win);
	map = get_mock_map();
	win.map = map;
	win.img = &img;
	check_map(map);
	win.mlxptr = mlx_init();
	if (!win.mlxptr)
		return (1);
	img.line_len = 0;
	img.bpp = 4;
	win.winptr = mlx_new_window(win.mlxptr, WIDTH, HEIGHT, "cub3d");
	if (!win.winptr)
	{
		free(win.mlxptr);
		return (1);
	}
	mlx_hook(win.winptr, KeyPress, KeyPressMask, handle_keypress, &win);
	mlx_hook(win.winptr, DestroyNotify, 0, close_win, &win);
	img.img = mlx_new_image(win.mlxptr, WIDTH, HEIGHT);
	if (!img.img)
		return (write(2, "!Error img\n", 11), close_win(&win, EXIT_FAILURE), 1);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.line_len, &img.endian);
	if (!img.addr)
		return (write(2, "Error addr\n", 12), free(img.img), close_win(&win, EXIT_FAILURE), 1);
	twod_map(map, &img);
	mlx_put_image_to_window(win.mlxptr, win.winptr, img.img, 0, 0);
	mlx_loop(win.mlxptr);
	close_win(&win, EXIT_FAILURE);
	return (0);
}