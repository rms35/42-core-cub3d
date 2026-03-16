/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 22:30:00 by rafael           ###   ########.fr       */
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

// Map
# define WIDTH 1920
# define HEIGHT 1080
# define N_KEYS 65536

// Player
# define PLAYER_DIR "WNSE"
# define M_SENS 0.0015

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
	int		pitch;
	int		m_delta_x;
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

typedef struct s_win
{
	void		*winptr;
	void		*mlxptr;
	t_img		*img;
	t_map		*map;
	t_player	*player;
	int			keys[N_KEYS];
	int			exit_status;
}	t_win;

// Mapping
t_map			*get_mock_map(void);
void			init_player(t_player *p, const t_map *map, double fov);
void			setup_mlx(t_win *win, t_img *img);
int				close_win(const t_win *win);

// Player movement
int				mouse_hook(int x, int y, const t_win *win);
int				move_player(const t_win *win, double dx, double dy);
void			rot_x_axis(t_player *p, double angle);
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

#endif
