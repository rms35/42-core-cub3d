/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:32:24 by rafael-m          #+#    #+#             */
/*   Updated: 2026/03/26 10:33:01 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

t_map	*parsing(const int argc, const char **argv)
{
	t_map	*map;

	if (argc != 2)
		return (write(2, "Error: invalid number of maps\n", 31), NULL);
	
	return (map);
}