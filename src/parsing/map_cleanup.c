/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_cleanup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:56:33 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 16:45:18 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	free_lines(t_list **lines)
{
	ft_lstclear(lines, free);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	free(map->grid);
	free(map->no_path);
	free(map->so_path);
	free(map->we_path);
	free(map->ea_path);
	free(map);
}
