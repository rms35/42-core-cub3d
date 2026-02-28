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

typedef struct s_win
{
	void    *winptr;
	void    *mlxptr;
}	t_win;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	camp_x;
	double	camp_y;
	double	camp_mod;
}	t_player;

typedef struct s_ray
{
	double	x;
	double	y;
}	t_ray;

typedef struct s_img
{
	void    *img;
	char    *addr;
	int		line_len;
	int		bpp;
	int		endian;
}	t_img;

typedef struct s_wall
{
	void    *img;
	char    *addr;
	int		line_len;
	int		total;
	int		bpp;
	int		endian;
}	t_wall;

t_map	*get_mock_map(void);

#endif
