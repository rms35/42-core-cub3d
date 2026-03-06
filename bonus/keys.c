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

#include "../includes/cub3d.h"

int	key_press(const int keysym, t_win *win)
{
	if (keysym == XK_Escape)
		close_win(win, EXIT_SUCCESS);
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
