/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 12:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/02/13 12:00:00 by rafael           ###   ########.fr       */
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
# define WIDTH 600
# define HEIGHT 600
# define FACTOR 100

typedef struct s_map
{
	char	*grid;
	int		width;
	int		height;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceil_color;
}	t_map;

typedef struct s_img
{
	void    *img;
	char    *addr;
	int		line_len;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	camp_x;
	double	camp_y;
	double	camp_mod;
	double	speed;
	double	turn_speed;
	int		grid_pos;
	double    cos_l;
	double    sin_l;
	double    cos_r;
	double    sin_r;
}	t_player;

typedef struct s_win
{
	void		*winptr;
	void	    *mlxptr;
	t_img		*img;
	t_map		*map;
	t_player	*player;
}	t_win;

typedef struct s_ray
{
	double	x;
	double	y;
}	t_ray;

// Mapping

t_map	*get_mock_map(void);

// Player movement

int		move_up(char *grid, int width, t_player *player);
int		move_down(char *grid, int width, t_player *player);
int		move_left(char *grid, int width, t_player *player);
int		move_right(char *grid, int width, t_player *player);
int		rotate_left(t_player *player);
int		rotate_right(t_player *player);

// Rendering
void	twod_map(const t_map *map, const t_img *img);


// To remove later
void	check_map(const t_map *map);

#endif
