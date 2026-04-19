/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by almorene          #+#    #+#             */
/*   Updated: 2026/04/19 15:20:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static size_t	get_line_width(char *line)
{
	size_t	length;

	length = ft_strlen(line);
	if (length > 0 && line[length - 1] == '\n')
		length--;
	return (length);
}

static void	fill_row(char *destination, char *source, size_t width)
{
	size_t	i;

	i = 0;
	while (source[i] && source[i] != '\n' && i < width)
	{
		destination[i] = source[i];
		i++;
	}
	while (i < width)
	{
		destination[i] = ' ';
		i++;
	}
}

static size_t	calculate_max_width(t_list *map_lines)
{
	t_list	*current;
	size_t	max_width;
	size_t	current_width;

	current = map_lines;
	max_width = 0;
	while (current)
	{
		current_width = get_line_width((char *)current->content);
		if (current_width > max_width)
			max_width = current_width;
		current = current->next;
	}
	return (max_width);
}

int	build_grid(t_map *map, t_list *map_lines)
{
	t_list	*current;
	size_t	row;

	map->height = (size_t)ft_lstsize(map_lines);
	map->width = calculate_max_width(map_lines);
	map->grid = ft_calloc((map->width * map->height) + 1, sizeof(char));
	if (!map->grid)
		return (error_msg("Memory allocation failed"));
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
