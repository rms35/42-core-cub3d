/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 19:02:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 12:00:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

#ifdef LINUX

void	cub3d_mouse_move(t_win *win, int x, int y)
{
	mlx_mouse_move(win->mlxptr, win->winptr, x, y);
}

void	cub3d_mouse_show(t_win *win)
{
	mlx_mouse_show(win->mlxptr, win->winptr);
}

void	cub3d_mouse_hide(t_win *win)
{
	mlx_mouse_hide(win->mlxptr, win->winptr);
}

#endif
