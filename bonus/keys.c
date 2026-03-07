/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 20:00:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 20:00:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int	key_press(const int keysym, t_win *win)
{
	if (keysym == XK_Escape)
	{
		win->exit_status = EXIT_SUCCESS;
		close_win(win);
	}
	if (keysym == XK_space && win->player->jump_t < 0)
		win->player->jump_t = 0.0;
	if (keysym < 65536)
		win->keys[keysym] = 1;
	return (0);
}

int	key_release(const int keysym, t_win *win)
{
	if (keysym < 65536)
		win->keys[keysym] = 0;
	return (0);
}
