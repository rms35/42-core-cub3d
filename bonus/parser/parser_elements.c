/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_elements.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 22:55:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 22:55:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parse_color(char *line)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		res;

	rgb = ft_split(line, ',');
	if (!rgb || ft_doubleptr_len((void **)rgb) != 3)
		return (ft_free_d(rgb), -1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_free_d(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	res = (r << 16) | (g << 8) | b;
	return (res);
}

static int	set_element(t_map *map, char *id, char *val)
{
	if (ft_strcmp(id, "NO") == 0 && !map->no_path)
		map->no_path = ft_strtrim(val, " \n");
	else if (ft_strcmp(id, "SO") == 0 && !map->so_path)
		map->so_path = ft_strtrim(val, " \n");
	else if (ft_strcmp(id, "WE") == 0 && !map->we_path)
		map->we_path = ft_strtrim(val, " \n");
	else if (ft_strcmp(id, "EA") == 0 && !map->ea_path)
		map->ea_path = ft_strtrim(val, " \n");
	else if (ft_strcmp(id, "SK") == 0 && !map->sky_path)
		map->sky_path = ft_strtrim(val, " \n");
	else if (ft_strcmp(id, "F") == 0 && map->floor_color == 0)
		map->floor_color = parse_color(val);
	else if (ft_strcmp(id, "C") == 0 && map->ceil_color == 0)
		map->ceil_color = parse_color(val);
	else
		return (0);
	return (1);
}

static int	process_element_line(t_map *map, char *line)
{
	char	*id;
	char	*val;
	int		res;

	line = skip_spaces(line);
	if (!*line || *line == '\n')
		return (1);
	id = line;
	while (*line && !ft_isspace(*line))
		line++;
	if (!*line)
		return (0);
	*line = '\0';
	val = skip_spaces(line + 1);
	res = set_element(map, id, val);
	return (res);
}

int	all_elements_filled(t_map *map)
{
	return (map->no_path && map->so_path && map->we_path && map->ea_path
		&& map->floor_color != -1 && map->ceil_color != -1);
}

int	parse_elements(t_map *map, int fd)
{
	char	*line;

	map->floor_color = -1;
	map->ceil_color = -1;
	map->sky_path = NULL;
	line = get_next_line_parser(fd);
	while (line)
	{
		if (!is_empty_line(line))
		{
			if (!process_element_line(map, line))
				return (free(line), 0);
		}
		free(line);
		if (all_elements_filled(map))
			return (1);
		line = get_next_line_parser(fd);
	}
	return (0);
}
