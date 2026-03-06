/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_dummy.c                                     :+:      |:    |:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 18:30:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 18:30:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	render_floor(const t_win *win, const t_ray *ray, int x, double p)
{
	(void)win;
	(void)ray;
	(void)x;
	(void)p;
}

void	render_ceil(const t_win *win, const t_ray *ray, int x, double p)
{
	(void)win;
	(void)ray;
	(void)x;
	(void)p;
}

unsigned int	apply_fog(unsigned int color, double dist, double p)
{
	(void)dist;
	(void)p;
	return (color);
}
