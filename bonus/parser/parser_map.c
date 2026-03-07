/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 23:05:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 23:05:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	get_max_width(t_list *lines)
{
	int	max;
	int	len;

	max = 0;
	while (lines)
	{
		len = ft_strlen((char *)lines->content);
		if (len > 0 && ((char *)lines->content)[len - 1] == '\n')
			len--;
		if (len > max)
			max = len;
		lines = lines->next;
	}
	return (max);
}

static char	*flatten_grid(t_map *map, t_list *lines)
{
	char	*grid;
	int		i;
	int		j;
	int		len;

	grid = malloc(map->width * map->height + 1);
	if (!grid)
		return (NULL);
	i = 0;
	while (lines)
	{
		len = ft_strlen((char *)lines->content);
		if (len > 0 && ((char *)lines->content)[len - 1] == '\n')
			len--;
		ft_memcpy(grid + i * map->width, lines->content, len);
		j = len;
		while (j < map->width)
			grid[i * map->width + j++] = ' ';
		i++;
		lines = lines->next;
	}
	grid[map->width * map->height] = '\0';
	return (grid);
}

int	parse_grid(t_map *map, int fd)
{
	t_list	*lines;
	char	*line;

	lines = NULL;
	line = get_next_line_parser(fd);
	while (line && is_empty_line(line))
	{
		free(line);
		line = get_next_line_parser(fd);
	}
	while (line)
	{
		ft_lstadd_back(&lines, ft_lstnew(line));
		line = get_next_line_parser(fd);
	}
	if (!lines)
		return (0);
	map->height = ft_lstsize(lines);
	map->width = get_max_width(lines);
	map->grid = flatten_grid(map, lines);
	ft_lstclear(&lines, free);
	return (map->grid != NULL);
}
