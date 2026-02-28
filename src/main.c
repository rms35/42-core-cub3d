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
	exit(keysym);
}

int	escape(const int keysym, void *data)
{
	t_win	*win;

	win = (t_win *)data;
	if (keysym == XK_Escape)
		close_win(win, EXIT_SUCCESS);
	return (0);
}

int	destroy_notify(const int keysym, void *data)
{
	t_win	*win;

	win = (t_win *)data;
	return (close_win(win, keysym));
}

// int	put_wall(char *wall, const int height, const int length)
// {
// 	int	i;
// 	int	j;
//
// 	i = 0;
// 	while (i < length)
// 	{
// 		j = 0;
// 		while (j < height)
// 		{
// 			wall[i + j] = 0xFF;
// 			j++;
// 		}
// 		i++;
// 	}
// }

void	init_data(t_win *win)
{
	win->mlxptr = NULL;
	win->winptr = NULL;
	// win->img = NULL;
	// win->addr = NULL;
}

void	my_mlx_pixel_put(const t_wall *wall, const int x, const int y, const int color)
{
	char	*dst;

	dst = wall->addr + (y * wall->line_len + x * (wall->bpp / 8));
	*(unsigned int*)dst = color;
}

// void set_wall(const t_wall *wall, const int margin)
// {
// 	int	x;
// 	int	y;
//
// 	x = 0;
// 	while (x < wall->width - (margin * 2))
// 	{
// 		y = 0;
// 		while (y < wall->heigth - (margin * 2))
// 		{
// 			my_mlx_pixel_put(wall, x + margin, y + margin, 0x00FF0000);
// 			y++;
// 			// printf("%d, %d\n", x, y);
// 		}
// 		x++;
// 	}
// }
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
int	main(const int argc, char **argv)
{
	t_win	win;
	t_wall	wall;

	if (argc != 3)
		return (write(2, "Error: width and length required\n", 34), 1);
	init_data(&win);
	win.mlxptr = mlx_init();
	if (!win.mlxptr)
		return (1);
	wall.line_len = 0;

	win.winptr = mlx_new_window(win.mlxptr, wall.width, wall.heigth, "cub3d");
	if (!win.winptr)
	{
		free(win.mlxptr);
		return (1);
	}
	wall.total = wall.heigth * wall.width;
	wall.bpp = 4;
	mlx_hook(win.winptr, KeyPress, KeyPressMask, escape, &win);
	mlx_hook(win.winptr, DestroyNotify, 0, close_win, &win);
	wall.img = mlx_new_image(win.mlxptr, wall.width, wall.heigth);
	if (!wall.img)
		return (write(2, "!Error img\n", 11), close_win(&win, EXIT_FAILURE), 1);
	wall.addr = mlx_get_data_addr(wall.img, &wall.bpp, &wall.line_len, &wall.endian);
	if (!wall.addr)
		return (write(2, "Error addr\n", 12), free(wall.img), close_win(&win, EXIT_FAILURE), 1);
	mlx_put_image_to_window(win.mlxptr, win.winptr, wall.img, 0, 0);
	mlx_loop(win.mlxptr);
	close_win(&win, EXIT_FAILURE);
	return (0);
}