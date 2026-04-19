/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 16:25:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

int	parse_rgb(const char *str, int *color)
{
	int			r;
	int			g;
	int			b;
	const char	*ptr;

	ptr = str;
	if (parse_channel(&ptr, &r))
		return (1);
	if (*ptr != ',')
		return (1);
	ptr++;
	if (parse_channel(&ptr, &g))
		return (1);
	if (*ptr != ',')
		return (1);
	ptr++;
	if (parse_channel(&ptr, &b))
		return (1);
	ptr = skip_spaces((char *)ptr);
	if (*ptr && *ptr != '\n')
		return (1);
	*color = (r << 16) | (g << 8) | b;
	return (0);
}

static int	parse_color_line(char *line, int *color)
{
	if (*color != -1)
		return (error_msg("Duplicate color identifier"));
	line = skip_spaces(line);
	if (parse_rgb(line, color))
		return (error_msg("Invalid RGB color"));
	return (0);
}

int	parse_identifier(char *line, t_map *map)
{
	if (!ft_strncmp(line, "NO ", 3))
		return (set_texture_path(&map->no_path, line + 3));
	if (!ft_strncmp(line, "SO ", 3))
		return (set_texture_path(&map->so_path, line + 3));
	if (!ft_strncmp(line, "WE ", 3))
		return (set_texture_path(&map->we_path, line + 3));
	if (!ft_strncmp(line, "EA ", 3))
		return (set_texture_path(&map->ea_path, line + 3));
	if (!ft_strncmp(line, "F ", 2))
		return (parse_color_line(line + 2, &map->floor_color));
	if (!ft_strncmp(line, "C ", 2))
		return (parse_color_line(line + 2, &map->ceil_color));
	return (-1);
}

int	is_empty_line(char *line)
{
	line = skip_spaces(line);
	return (*line == '\0' || *line == '\n');
}

int	is_map_char(char c)
{
	if (c == ' ' || c == '0' || c == '1' || c == '2' || c == 'F')
		return (1);
	if (ft_strchr(PLYR_DIR, c))
		return (1);
	return (0);
}
