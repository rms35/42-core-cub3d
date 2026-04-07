/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:40:00 by rafael-m          #+#    #+#             */
/*   Updated: 2026/03/28 12:40:00 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include <stdint.h>

static void	clear_q(t_list **q)
{
	t_list	*curr;

	while (*q)
	{
		curr = *q;
		*q = (*q)->next;
		free(curr);
	}
}

static int	check_one(const t_map *map, int x, int y, t_list **q)
{
	int	idx;

	if (x < 0 || y < 0 || x >= (int)map->width || y >= (int)map->height)
		return (write(2, "Error: Map is not closed\n", 25), 1);
	idx = y * map->width + x;
	if (map->grid[idx] == ' ' || map->grid[idx] == '\0')
		return (write(2, "Error: Map is not closed\n", 25), 1);
	if ((map->grid[idx] == '0' || (map->grid[idx] != '\0'
				&& ft_strchr(PLYR_DIR, map->grid[idx]))))
	{
		if (map->grid[idx] != 'V')
		{
			map->grid[idx] = 'V';
			ft_lstadd_back(q, ft_lstnew((void *)(uintptr_t)idx));
		}
	}
	return (0);
}

static int	flood_fill(const t_map *map, const int start)
{
	t_list	*q;
	t_list	*curr;
	int		idx;

	q = ft_lstnew((void *)(uintptr_t)start);
	if (!q)
		return (1);
	map->grid[start] = 'V';
	while (q)
	{
		curr = q;
		idx = (int)(uintptr_t)curr->content;
		q = q->next;
		free(curr);
		if (check_one(map, idx % map->width + 1, idx / map->width, &q)
			|| check_one(map, idx % map->width - 1, idx / map->width, &q)
			|| check_one(map, idx % map->width, idx / map->width + 1, &q)
			|| check_one(map, idx % map->width, idx / map->width - 1, &q))
		{
			clear_q(&q);
			return (1);
		}
	}
	return (0);
}

int	validate_map(t_map *map)
{
	int		i;
	char	*grid_copy;

	grid_copy = ft_calloc(map->width * map->height + 1, sizeof(char));
	if (!grid_copy)
		return (1);
	ft_memcpy(grid_copy, map->grid, map->width * map->height);
	i = -1;
	while (++i < (int)(map->width * map->height))
	{
		if ((map->grid[i] == '0' || (map->grid[i] != '\0'
					&& ft_strchr(PLYR_DIR, map->grid[i]))))
		{
			if (flood_fill(map, i))
			{
				free(map->grid);
				map->grid = grid_copy;
				return (1);
			}
		}
	}
	free(map->grid);
	map->grid = grid_copy;
	return (0);
}
