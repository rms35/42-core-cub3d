/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 10:57:30 by rafael-m          #+#    #+#             */
/*   Updated: 2026/03/21 10:59:30 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_BONUS_H
# define STRUCT_BONUS_H

# include <stddef.h>
# include "macros_bonus.h"

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	char	*grid;
	size_t	width;
	size_t	height;
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

typedef struct s_sprite
{
	double	x;
	double	y;
	double	dist;
	double	trans_x;
	double	trans_y;
	t_img	*tex;
	void	(*animation)(struct s_sprite *s, double time);
	double	last_update;
	double	anim_speed;
	int		frame_count;
	int		current_frame;
	int		next_frame;
	int		sprite_id;
	double	door_offs;
	int		open;
	int		opening;
	int		closing;
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
	double	perp_dist;
	double	ray_mag;
	double	wall_x;
	double	tex_step;
	double	tex_pos;
	t_img	*tex;
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
	t_img			fire[N_FIRES];
	t_img			*door;
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
	int				minilu[257];
	int				exit_status;
	size_t			n_sprites;
}	t_win;

#endif
