/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by almorene          #+#    #+#             */
/*   Updated: 2026/04/12 00:00:00 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	add_map_line(t_list **map_lines, const char *line)
{
	t_list	*node;

	node = ft_lstnew(ft_strdup(line));
	if (!node || !node->content)
		return (free(node), error_msg("Memory allocation failed"));
	ft_lstadd_back(map_lines, node);
	return (0);
}

int	is_config_full(const t_map *map)
{
	return (map->no_path && map->so_path && map->we_path
		&& map->ea_path && map->floor_color != -1
		&& map->ceil_color != -1);
}

static int	not_seen(t_list **map_lines, char *line)
{
	if (is_empty_line(line))
		return (error_msg("Empty line inside map"));
	if (!looks_like_map_block(line))
		return (error_msg("Invalid content after map start"));
	if (add_map_line(map_lines, line))
		return (1);
	return (0);
}

static int	parse_line(char *line, t_map *map, t_list **map_lines, int *seen)
{
	int	status;

	if (is_empty_line(line))
		return (0);
	if (is_map_line(line))
	{
		*seen = 1;
		if (add_map_line(map_lines, line))
			return (1);
		return (0);
	}
	line = skip_spaces(line);
	status = parse_identifier(line, map);
	if (status == -1)
		return (error_msg("Invalid configuration line"));
	if (status == 1)
		return (1);
	return (0);
}

int	parse_config_lines(const t_list *lines, t_map *map, t_list **map_lines)
{
	char	*line;
	int		seen_map;

	seen_map = 0;
	while (lines)
	{
		line = (char *)lines->content;
		if (!seen_map)
		{
			if (parse_line(line, map, map_lines, &seen_map))
				return (1);
		}
		else if (not_seen(map_lines, line))
			return (1);
		lines = lines->next;
	}
	if (!is_config_full(map))
		return (error_msg("Missing configuration"));
	if (!*map_lines)
		return (error_msg("Missing map"));
	return (0);
}
