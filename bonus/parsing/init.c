/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/02 14:45:00 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

# define P1_TURNSP 0.013
# define P1_R 0.2

static void    get_dir(t_player *p, const char c)
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

void   init_player(t_player *p, const t_map *map, const double fov)
{
       size_t                          i;

       ft_bzero(p, sizeof(t_player));
       i = 0;
       while (i < map->width * map->height)
       {
           if (map->grid[i] != '\0' && ft_strchr(PLYR_DIR, map->grid[i]))
               break ;
           i++;
       }
       if (i >= map->width * map->height)
       {
               write(2, "Error: No player found in map\n", 30);
               exit(1);
       }
       p->pos_x = (double)(i % map->width) + 0.5;
       p->pos_y = (double)(i / map->width) + 0.5;
       get_dir(p, map->grid[i]);
       map->grid[i] = '0';
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
       p->fwd_speed = P1_SPEED;
       p->rot_speed = P1_ROT_SPEED;
}

void    alloc_sprites(t_win *win)
{
        size_t     i;

        i = 0;
        while (i < win->map->height * win->map->width)
        {
                if (win->map->grid[i] == 'D' || win->map->grid[i] == 'F')
                        win->n_sprites++;
                i++;
        }
       win->sprites = ft_calloc(win->n_sprites, sizeof(t_sprite));
       if (!win->sprites)
       {
               free(win->z_buffer);
               write(2, "Error: malloc\n", 8);
               exit(EXIT_FAILURE);
       }
       i = 0;
       while (i < win->n_sprites)
       {
               win->sprites[i].tex = ft_calloc(N_FIRES, sizeof(t_img));
               if (!win->sprites[i].tex)
                       exit(EXIT_FAILURE);
               i++;
       }
       win->sprite_dist = ft_calloc(win->n_sprites, sizeof(double));
       if (!win->sprite_dist)
       {
               free(win->z_buffer);
               free(win->sprites);
               write(2, "Error: malloc\n", 8);
               exit(EXIT_FAILURE);
       }
       win->sprite_order = ft_calloc(win->n_sprites, sizeof(int));
       if (!win->sprite_order)
       {
               free(win->z_buffer);
               free(win->sprites);
               free(win->sprite_dist);
               write(2, "Error: malloc\n", 8);
               exit(EXIT_FAILURE);
       }
}

void   setup_mlx(t_win *win, t_img *img)
{
       win->exit_status = EXIT_SUCCESS;
       win->mlxptr = mlx_init();
       if (!win->mlxptr)
       {
               write(2, "Error: mlx_init\n", 16);
               exit(1);
       }
       img->line_len = 0;
       img->bpp = 4;
       win->winptr = mlx_new_window(win->mlxptr, WIDTH, HEIGHT, "cub3d");
       if (!win->winptr)
       {
               write(2, "Error: mlx_new_window\n", 22);
               exit(1);
       }
       mlx_hook(win->winptr, EVENT_KEY_PRESS, MASK_KEY_PRESS, (int (*)())(void *)key_press, win);
       mlx_hook(win->winptr, EVENT_KEY_RELEASE, MASK_KEY_RELEASE, (int (*)())(void *)key_release, win);
       mlx_hook(win->winptr, EVENT_DESTROY_NOTIFY, 0, (int (*)())(void *)close_win, win);
       mlx_hook(win->winptr, EVENT_MOTION_NOTIFY, MASK_POINTER_MOTION, (int (*)())(void *)mouse_hook, win);
       img->img = mlx_new_image(win->mlxptr, WIDTH, HEIGHT);
       if (!img->img)
       {
               win->exit_status = EXIT_FAILURE;
               write(2, "Error: mlx_new_image\n", 21);
               close_win(win);
       }
       img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
                       &img->endian);
       if (!img->addr)
       {
               win->exit_status = EXIT_FAILURE;
               write(2, "Error: mlx_get_data_addr\n", 25);
               close_win(win);
       }
       img->width = WIDTH;
       img->height = HEIGHT;
       mlx_mouse_move(win->mlxptr, win->winptr, WIDTH / 2, HEIGHT / 2);
       mlx_mouse_hide(win->mlxptr, win->winptr);
}

int	init_textures(t_win *win)
{
	if (load_texture(win, &win->textures[W1N], win->map->no_path)
		|| load_texture(win, &win->textures[W1S], win->map->so_path)
		|| load_texture(win, &win->textures[W1W], win->map->we_path)
		|| load_texture(win, &win->textures[W1E], win->map->ea_path))
		return (1);
	return (0);
}
