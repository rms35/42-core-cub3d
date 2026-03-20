/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/20 12:43:33 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <X11/keysym.h>
# include <X11/X.h>
# include <time.h>

// Screen & Map

# define WIDTH 1920
# define HEIGHT 1080
# define N_KEYS 65536
# define N_SPRITES 100
# define FRAME_DELAY 33.3333

// Player

# define PLYR_DIR "WNSE"
# define M_SENS 0.0015
# define P1_SPEED 2.0
# define P1_ROT_SPEED 1.0

// Textures

# define TEX_WIDTH 512
# define TEX_HEIGHT 512
# define N_TEX 6
# define W1N 0
# define W1S 1
# define W1W 2
# define W1E 3
# define S1 4
# define F1 5

// Sprites

# define FIRE 1
# define FIRE_T 100
# define WALK_T 150
# define IDLE_T 300
# define N_FIRES 4
# define F_RADIUS 0.1

typedef struct s_sprt_types
{
	int	fires[2];
	int	total;
}	t_sprt_types;

typedef struct s_map
{
	char	*grid;
	int		width;
	int		height;
	int		floor_color;
	int		ceil_color;
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

typedef struct s_sprite
{
	double			x;
	double			y;
	double			dist;
	double			trans_x;
	double			trans_y;
	t_img			*tex;
	t_sprt_types	*types;
	void			(*animation)(struct s_sprite *s, double time);
	double			last_update;
	long			anim_speed;
	int				frame_count;
	int				current_frame;
	int				next_frame;
	int				sprite_id;
}	t_sprite;

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
	double	fwd_speed;
	double	rot_speed;
	double	cos_l;
	double	sin_l;
	double	cos_r;
	double	sin_r;
	double	fov;
	double	radius;
	int		m_delta_x;
	int		m_delta_y;
	int		pitch;
}	t_player;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	ray_mag;
	double	wall_x;
	double	tex_step;
	double	tex_pos;
	int		wall_tex;
	int		ceiling_tex;
	int		floor_tex;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_sprite_draw
{
	int		sprite_screen_x;
	int		sprite_height;
	int		sprite_width;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
	int		tex_x;
	int		tex_y;
}	t_sprite_draw;

typedef struct s_pair
{
	double	dist;
	int		index;
}	t_pair;

typedef struct s_win
{
	t_img			textures[N_TEX];
	void			*winptr;
	void			*mlxptr;
	t_img			*img;
	t_map			*map;
	t_player		*player;
	double			current_time;
	double			last_frame;
	double			delta_time;
	int				*keys;
	t_sprite		*sprites;
	double			*sprite_dist;
	double			*z_buffer;
	int				*sprite_order;
	int				exit_status;

}	t_win;

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
