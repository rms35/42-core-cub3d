/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 14:00:00 by rafael-m          #+#    #+#             */
/*   Updated: 2026/04/02 14:00:00 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parse_rgb(char *str)
{
	char	**rgb;
	int		r;
	int		g;
	int		b;
	int		i;

	rgb = ft_split(str, ',');
	if (!rgb)
		return (-1);
	i = 0;

	while (rgb[i])
		i++;
	if (i != 3)
		return (ft_free_d(rgb), -1);
	r = ft_atoi(rgb[0]);
	g = ft_atoi(rgb[1]);
	b = ft_atoi(rgb[2]);
	ft_free_d(rgb);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

static char	*extract_path(char *line)
{
	int		i;
	int		len;
	char	*path;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		line++;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		len--;
	path = ft_strndup(line, len);
	return (path);
}

int	parse_line_config(char *line, t_map *map)
{
	while (*line && (*line == ' ' || *line == '\t'))
		line++;
	if (!*line || *line == '\n')
		return (0);
	if (!ft_strncmp(line, "NO ", 3) && !map->no_path)
		map->no_path = extract_path(line + 3);
	else if (!ft_strncmp(line, "SO ", 3) && !map->so_path)
		map->so_path = extract_path(line + 3);
	else if (!ft_strncmp(line, "WE ", 3) && !map->we_path)
		map->we_path = extract_path(line + 3);
	else if (!ft_strncmp(line, "EA ", 3) && !map->ea_path)
		map->ea_path = extract_path(line + 3);
	else if (!ft_strncmp(line, "F ", 2) && map->floor_color == -1)
		map->floor_color = parse_rgb(line + 2);
	else if (!ft_strncmp(line, "C ", 2) && map->ceil_color == -1)
		map->ceil_color = parse_rgb(line + 2);
	else
		return (-1);
	return (1);
}

int	is_config_full(t_map *map)
{
	return (map->no_path && map->so_path && map->we_path && map->ea_path
		&& map->floor_color != -1 && map->ceil_color != -1);
}
