/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 22:30:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/stat.h>

// Map

# define WIDTH 1920
# define HEIGHT 1080
# define N_KEYS 7
# define N_TEX 4
# define CEILING 0x87CEEB
# define FLOOR 0x4B4B4B

// Player

# define PLYR_DIR "WNSE"

// Keys

# ifdef LINUX
#  define W_KEY       119
#  define A_KEY       97
#  define S_KEY       115
#  define D_KEY       100
#  define LARRW_KEY   65361
#  define RARRW_KEY   65363
#  define ESC_KEY     65307
# elif defined(MACOS)
#  define W_KEY       13
#  define A_KEY       0
#  define S_KEY       1
#  define D_KEY       2
#  define LARRW_KEY   123
#  define RARRW_KEY   124
#  define ESC_KEY     53
# endif

# define W 0
# define A 1
# define S 2
# define D 3
# define LA 4
# define RA 5

/* MiniLibX/X11 Event Codes */

# define EVENT_KEY_PRESS      2
# define EVENT_KEY_RELEASE    3
# define EVENT_DESTROY_NOTIFY 17

/* MiniLibX/X11 Event Masks */

# define MASK_KEY_PRESS       0x000001
# define MASK_KEY_RELEASE     0x000002

# define TEX_NORTH 0
# define TEX_SOUTH 1
# define TEX_WEST 2
# define TEX_EAST 3

# define P1_TURNSP 0.033
# define P1_SPEED 0.03
# define P1_R 0.2

typedef struct s_map
{
	char	*grid;
	int		width;
	int		height;
	int		floor_color;
	int		ceil_color;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		line_len;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	dir_mag;
	double	camp_x;
	double	camp_y;
	double	speed;
	double	rot_speed;
	double	cos_l;
	double	sin_l;
	double	cos_r;
	double	sin_r;
	double	fov;
	double	radius;
}	t_player;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_dist;
	double	ray_mag;
	double	wall_x;
	double	tex_step;
	double	tex_pos;
	int		map_x;
	int		map_y;
	int		wall_tex;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_win
{
	t_img		textures[N_TEX];
	void		*winptr;
	void		*mlxptr;
	t_img		*img;
	t_map		*map;
	t_player	*player;
	int			keys[N_KEYS];
	int			exit_status;
}	t_win;

// Parsing Config

int				parse_identifier(char *line, t_map *map);
int				parse_config_lines(const t_list *lines, t_map *map,
					t_list **map_lines);
int				is_config_full(const t_map *map);
int				parse_rgb(const char *str, int *color);
int				is_empty_line(char *line);
int				is_map_line(char *line);
int				parse_channel(const char **str, int *value);
int				set_texture_path(char **slot, char *line);
int				looks_like_map_block(char *line);
char			*skip_spaces(char *str);
int				is_valid_texture_path(const char *path);

// Parsing map

int				validate_map(t_map *map);
int				parse_map_file(t_map **map, int argc, char **argv);
int				build_grid(t_map *map, t_list *map_lines);
int				error_msg(const char *msg);

// Initializing resources

void			init_player(t_player *p, const t_map *map, double fov);
void			setup_mlx(t_win *win, t_img *img);
int				init_textures(t_win *win);
int				load_texture(const t_win *win, t_img *tex, char *path);

// Player movement

int				move_player(const t_win *win, double dx, double dy);
int				rotate_player(t_player *p, double angle);
int				rotate_left(t_player *player);
int				rotate_right(t_player *player);

// Rendering

void			render_frame(const t_win *win);
void			init_ray(const t_win *win, t_ray *ray, int x);
void			perform_dda(const t_win *win, t_ray *ray);
int				key_press(int keysym, t_win *win);
int				key_release(int keysym, t_win *win);
int				handle_input(const t_win *win);
int				game_loop(const t_win *win);

// Cleanup

int				close_win(const t_win *win);
void			free_lines(t_list **lines);
void			free_map(t_map *map);

#endif
