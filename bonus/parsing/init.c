/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 14:45:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static void	setup_main_image(t_win *win, t_img *img)
{
	img->img = mlx_new_image(win->mlxptr, WIDTH, HEIGHT);
	if (!img->img)
	{
		win->exit_status = EXIT_FAILURE;
		write(2, "Error: mlx_new_image\n", 21);
		close_win(win);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	img->width = WIDTH;
	img->height = HEIGHT;
}

static void	setup_mlx_hooks(t_win *win)
{
	mlx_hook(win->winptr, EVENT_KEY_PRESS, MASK_KEY_PRESS,
		(void *)key_press, win);
	mlx_hook(win->winptr, EVENT_KEY_RELEASE, MASK_KEY_RELEASE,
		(void *)key_release, win);
	mlx_hook(win->winptr, EVENT_DESTROY_NOTIFY, 0,
		(void *)close_win, win);
	mlx_hook(win->winptr, EVENT_MOTION_NOTIFY, MASK_POINTER_MOTION,
		(void *)mouse_hook, win);
}

void	setup_mlx(t_win *win, t_img *img)
{
	win->exit_status = EXIT_SUCCESS;
	win->mlxptr = mlx_init();
	if (!win->mlxptr)
	{
		write(2, "Error: mlx_init\n", 16);
		exit(1);
	}
	win->winptr = mlx_new_window(win->mlxptr, WIDTH, HEIGHT, "cub3d");
	if (!win->winptr)
	{
		write(2, "Error: mlx_new_window\n", 22);
		exit(1);
	}
	setup_mlx_hooks(win);
	setup_main_image(win, img);
	mlx_mouse_move(win->mlxptr, win->winptr, WIDTH / 2, HEIGHT / 2);
	mlx_mouse_hide(win->mlxptr, win->winptr);
}

void	alloc_sprites(t_win *win)
{
	size_t	i;

	i = 0;
	while (i < win->map->height * win->map->width)
	{
		if (win->map->grid[i] == 'D' || win->map->grid[i] == 'F')
			win->n_sprites++;
		i++;
	}
	win->sprites = ft_calloc(win->n_sprites, sizeof(t_sprite));
	win->pairs = ft_calloc(win->n_sprites, sizeof(t_pair));
	win->sprite_dist = ft_calloc(win->n_sprites, sizeof(double));
	win->sprite_order = ft_calloc(win->n_sprites, sizeof(int));
	if (!win->sprites || !win->pairs || !win->sprite_dist || !win->sprite_order)
	{
		free(win->z_buffer);
		free(win->sprites);
		free(win->pairs);
		free(win->sprite_dist);
		free(win->sprite_order);
		write(2, "Error: malloc\n", 8);
		exit(EXIT_FAILURE);
	}
}
