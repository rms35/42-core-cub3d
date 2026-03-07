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
# include <X11/keysym.h>
# include <X11/X.h>
# define WIDTH 1920
# define HEIGHT 1080
# define BUFFER 0.2

typedef struct s_map
{
	char	*grid;
	int		width;
	int		height;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	char	*sky_path;
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
	double	camp_x;
	double	camp_y;
	double	speed;
	double	turn_speed;
	double	cos_l;
	double	sin_l;
	double	cos_r;
	double	sin_r;
	int		pitch;
	double	jump_t;
	double	pos_z;
}	t_player;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
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
	t_img		tex[6];
	t_img		sky_tex;
	t_img		*accum;
	int			keys[65536];
	double		pulse_time;
	int			mouse_x;
	int			mouse_y;
	int			exit_status;
}	t_win;

// Mapping

t_map			*get_mock_map(void);
void			init_player(t_player *p, char *grid, int width, int total);
void			setup_mlx(t_win *win, t_img *img);
int				close_win(t_win *win);

// Player movement

int				move_up(char *grid, int width, t_player *player);
int				move_down(char *grid, int width, t_player *player);
int				move_left(char *grid, int width, t_player *player);
int				move_right(char *grid, int width, t_player *player);
int				move_player(t_win *win, double dx, double dy);
int				rotate_player(t_player *p, double angle);
int				rotate_left(t_player *player);
int				rotate_right(t_player *player);

// Rendering
void			render_frame(const t_win *win);
void			render_env(const t_win *win, const t_ray *ray, int x,
					double p[2], double pos_z);
void			render_hud(const t_win *win);
unsigned int	apply_fog(unsigned int color, double dist, double p);
unsigned int	apply_fog_factor(unsigned int color, double f, double p);
void			init_ray(const t_win *win, t_ray *ray, int x);
void			perform_dda(const t_win *win, t_ray *ray);
void			get_pulses(const t_win *win, double p[6]);
void			setup_ray_limits(const t_win *win, t_ray *ray, double pos_z);
void			apply_motion_blur(const t_win *win);
int				key_press(int keysym, t_win *win);
int				key_release(int keysym, t_win *win);
int				mouse_move(int x, int y, t_win *win);
int				handle_input(t_win *win);
int				game_loop(t_win *win);

#endif
