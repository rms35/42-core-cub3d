/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by almorene          #+#    #+#             */
/*   Updated: 2026/04/12 00:00:00 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static size_t	line_width(const char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	return (len);
}

static void	fill_row(char *dst, const char *src, int width)
{
	int	i;

	i = 0;
	while (src[i] && src[i] != '\n' && i < width)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < width)
	{
		dst[i] = ' ';
		i++;
	}
}

static int	allocate_grid(t_map *map, t_list *map_lines)
{
	t_list	*current;
	size_t	width;

	current = map_lines;
	width = 0;
	map->height = ft_lstsize(map_lines);
	while (current)
	{
		if (line_width((char *)current->content) > width)
			width = line_width((char *)current->content);
		current = current->next;
	}
	map->width = (int)width;
	map->grid = ft_calloc((map->width * map->height) + 1, sizeof(char));
	if (!map->grid)
		return (error_msg("Memory allocation failed"));
	return (0);
}

int	build_grid(t_map *map, t_list *map_lines)
{
	t_list	*current;
	int		row;

	if (allocate_grid(map, map_lines))
		return (1);
	current = map_lines;
	row = 0;
	while (current)
	{
		fill_row(map->grid + (row * map->width), (char *)current->content,
			map->width);
		current = current->next;
		row++;
	}
	return (0);
}
