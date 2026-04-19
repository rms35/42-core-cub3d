/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by almorene          #+#    #+#             */
/*   Updated: 2026/04/19 15:10:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static int	is_map_line(char *line)
{
	int	has_map_char;

	line = skip_spaces(line);
	if (!*line || *line == '\n')
		return (0);
	has_map_char = 0;
	while (*line && *line != '\n')
	{
		if (!is_map_char(*line))
			return (0);
		if (*line != ' ')
			has_map_char = 1;
		line++;
	}
	return (has_map_char);
}

static int	looks_like_map_block(char *line)
{
	line = skip_spaces(line);
	if (!*line || *line == '\n')
		return (0);
	while (*line && *line != '\n')
	{
		if (*line != ' ')
			return (1);
		line++;
	}
	return (0);
}

static int	handle_pre_map(char *line, t_map *map, t_list **map_lines,
	int *seen_map)
{
	int	status;

	if (is_empty_line(line))
		return (0);
	if (is_map_line(line))
	{
		*seen_map = 1;
		return (add_map_line(map_lines, line));
	}
	status = parse_identifier(skip_spaces(line), map);
	if (status == -1)
		return (error_msg("Invalid configuration line"));
	return (status);
}

static int	handle_post_map(char *line, t_list **map_lines)
{
	if (is_empty_line(line))
		return (error_msg("Empty line inside map"));
	if (!looks_like_map_block(line))
		return (error_msg("Invalid content after map start"));
	return (add_map_line(map_lines, line));
}

int	parse_config_lines(t_list *lines, t_map *map, t_list **map_lines)
{
	char	*line;
	int		seen_map;

	seen_map = 0;
	while (lines)
	{
		line = (char *)lines->content;
		if (!seen_map)
		{
			if (handle_pre_map(line, map, map_lines, &seen_map))
				return (1);
		}
		else if (handle_post_map(line, map_lines))
			return (1);
		lines = lines->next;
	}
	if (!(map->no_path && map->so_path && map->we_path
			&& map->ea_path && map->floor_color != -1
			&& map->ceil_color != -1) || !*map_lines)
		return (error_msg("Missing configuration or map"));
	return (0);
}
