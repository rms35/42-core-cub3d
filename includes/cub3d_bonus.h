/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/21 11:00:59 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "macros_bonus.h"
# include "struct_bonus.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <time.h>

//  Initializing resources

void			init_player(t_player *p, const t_map *map,
					double fov);
void			setup_mlx(t_win *win, t_img *img);
int				alloc_sprites(t_win *win);
int				init_sprites(t_win *win, const t_map *map);
int				close_win(t_win *win);

double get_time(void);

// Mapping

t_map			*get_mock_map(t_win *win);
int				load_texture(const t_win *win, t_img *tex, char *path);

// Player movement

int				mouse_hook(int x, int y, t_win *win);
int				move_player(t_win *win, double dx, double dy);
void			rot_x_axis(t_player *p, double angle);
int				rotate_left(t_player *player);
int				rotate_right(t_player *player);

// Rendering

void			render_frame(t_win *win);
void			init_ray(const t_win *win, t_ray *ray, int x);
void			perform_dda(const t_win *win, t_ray *ray);
int				key_press(int keysym, t_win *win);
int				key_release(int keysym, t_win *win);
int				handle_input(t_win *win);
void			render_sprites(const t_win *win);
unsigned int	alpha_blend(unsigned int background, unsigned int foreground,
	float alpha);

// Sprite animation
void			animate_fire(t_sprite *s, double time);
void			animate_sprites(t_sprite *s, double time);

#endif
