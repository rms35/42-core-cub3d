/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 12:00:00 by rafael           ###   ########.fr       */
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
# include <time.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/stat.h>

// Parsing

t_map			*parsing(int argc, char **argv);
int				parse_config_lines(t_list *lines, t_map *map,
					t_list **map_lines);
int				build_grid(t_map *map, t_list *map_lines);
int				validate_map(t_map *map);
int				error_msg(const char *msg);
int				set_texture_path(char **slot, char *line);
int				add_map_line(t_list **map_lines, const char *line);
int				parse_channel(const char **str, int *value);
char			*skip_spaces(char *str);
int				is_map_char(char c);
int				is_empty_line(char *line);
int				parse_identifier(char *line, t_map *map);
int				read_cub_file(const char *path, t_list **lines);
void			free_lines(t_list **lines);
void			fill_from(t_map *map, char *visited, t_point p, int *open_map);
t_point			set_point(int x, int y);

//  Initializing resources

void			init_player(t_player *p, const t_map *map,
					double fov);
void			setup_mlx(t_win *win, t_img *img);
int				init_textures(t_win *win);
void			alloc_sprites(t_win *win);
int				init_sprites(t_win *win, t_map *map);
int				close_win(void *param);
int				init_doors(t_win *win);
int				load_texture(const t_win *win, t_img *tex, char *path);

double			get_time(void);

// Input management

int				mouse_hook(int x, int y, void *param);
int				move_player(t_win *win, double dx, double dy);
void			rot_x_axis(t_player *p, double angle);
int				rotate_left(t_player *player);
int				rotate_right(t_player *player);
void			handle_mouse_rotation(const t_win *win);
void			open_door(const t_win *win);

// Rendering

void			render_frame(t_win *win);
void			init_ray(t_win *win, t_ray *ray, int x);
void			perform_dda(t_win *win, t_ray *ray);
int				key_press(int keysym, void *param);
int				key_release(int keysym, void *param);
int				handle_input(t_win *win);
void			render_sprites(t_win *win);
void			render_door(t_win *win, const t_sprite *door);
void			render_minimap(t_map *map, t_img *img, t_win *win);
unsigned int	alpha_blend(unsigned int background, unsigned int foreground,
					float alpha);
int				door_dda(t_win *win, t_ray *ray, const t_sprite *door);
void			calculate_sprite_distances(t_win *win, t_pair *pairs);
void			sort_sprites(t_win *win);
void			calculate_draw_params(t_win *win, t_sprite *sprite,
					t_sprite_draw *draw);

// Sprite animation

void			animate_fire(t_sprite *s, double time);
void			animate_sprites(t_sprite *s, double time, size_t n_sprites);
void			animate_door(t_sprite *s, double time);
t_sprite		*get_door(t_sprite *s, size_t n_sprites, int next_x,
					int next_y);

// Cleanup

void			cleanup_textures(t_win *win);
void			cleanup_mlx(t_win *win);

#endif
