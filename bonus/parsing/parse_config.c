/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by almorene          #+#    #+#             */
/*   Updated: 2026/04/18 00:00:00 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"
#include <sys/stat.h>

static char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

static int	parse_channel(const char **str, int *value)
{
	int	result;

	*str = skip_spaces((char *)*str);
	if (!ft_isdigit(**str))
		return (1);
	result = 0;
	while (ft_isdigit(**str))
	{
		result = (result * 10) + (**str - '0');
		if (result > 255)
			return (1);
		(*str)++;
	}
	*str = skip_spaces((char *)*str);
	*value = result;
	return (0);
}

static int	add_map_line(t_list **map_lines, const char *line)
{
	t_list	*node;

	node = ft_lstnew(ft_strdup(line));
	if (!node || !node->content)
		return (free(node), error_msg("Memory allocation failed"));

ft_lstadd_back(map_lines, node);
	return (0);
}

static int	is_valid_texture_path(const char *path)
{
	size_t		len;
	struct stat	path_stat;

	len = ft_strlen(path);
	if (len < 5 || (ft_strncmp(path + len - 4, ".xpm", 4) != 0 && ft_strncmp(path + len - 4, ".png", 4) != 0))
		return (0);
	if (stat(path, &path_stat) != 0)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
		return (0);
	if (access(path, R_OK) != 0)
		return (0);
	return (1);
}

static int	set_texture_path(char **slot, char *line)
{
	char	*path;

	if (*slot)
		return (error_msg("Duplicate texture identifier"));
	line = skip_spaces(line);
	if (!*line || *line == '\n')
		return (error_msg("Missing texture path"));
	path = ft_strtrim(line, " \n");
	if (!path || !*path)
		return (free(path), error_msg("Missing texture path"));
	if (!is_valid_texture_path(path))
		return (free(path), error_msg("Invalid texture path"));
	*slot = path;
	return (0);
}

int	parse_rgb(const char *str, int *color)
{
	int	r;
	int	g;
	int	b;

	if (parse_channel(&str, &r))
		return (1);
	if (*str != ',')
		return (1);
	str++;
	if (parse_channel(&str, &g))
		return (1);
	if (*str != ',')
		return (1);
	str++;
	if (parse_channel(&str, &b))
		return (1);
	str = skip_spaces((char *)str);
	if (*str && *str != '\n')
		return (1);
	*color = (r << 16) | (g << 8) | b;
	return (0);
}

static int	parse_color_line(const char *line, int *color)
{
	if (*color != -1)
		return (error_msg("Duplicate color identifier"));
	line = skip_spaces((char *)line);
	if (parse_rgb(line, color))
		return (error_msg("Invalid RGB color"));
	return (0);
}

static int	parse_identifier(char *line, t_map *map)
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

static int	is_empty_line(char *line)
{
	line = skip_spaces(line);
	return (*line == '\0' || *line == '\n');
}

static int	is_map_line(char *line)
{
	int	has_map_char;

	line = skip_spaces(line);
	if (!*line || *line == '\n')
		return (0);
	has_map_char = 0;
	while (*line && *line != '\n')
	{
		if (*line != ' ' && *line != '0' && *line != '1' && *line != '2'
			&& *line != 'F' && !ft_strchr(PLYR_DIR, *line))
			return (0);
		if (*line == '0' || *line == '1' || *line == '2' || *line == 'F' || ft_strchr(PLYR_DIR, *line))
			has_map_char = 1;
		line++;
	}
	return (has_map_char);
}

static int	looks_like_map_block(char *line)
{
	int	has_non_space;

	line = skip_spaces(line);
	if (!*line || *line == '\n')
		return (0);
	has_non_space = 0;
	while (*line && *line != '\n')
	{
		if (*line != ' ')
			has_non_space = 1;
		line++;
	}
	return (has_non_space);
}

int	is_config_full(t_map *map)
{
	return (map->no_path && map->so_path && map->we_path
		&& map->ea_path && map->floor_color != -1
		&& map->ceil_color != -1);
}

int	parse_config_lines(const t_list *lines, t_map *map, t_list **map_lines)
{
	char	*line;
	int	seen_map;
	int	status;

	seen_map = 0;
	while (lines)
	{
		line = (char *)lines->content;
		if (!seen_map)
		{
			if (is_empty_line(line))
			{
				lines = lines->next;
				continue ;
			}
			if (is_map_line(line))
			{
				seen_map = 1;
				if (add_map_line(map_lines, line))
					return (1);
				lines = lines->next;
				continue ;
			}
			line = skip_spaces(line);
			status = parse_identifier(line, map);
			if (status == -1)
				return (error_msg("Invalid configuration line"));
			if (status == 1)
				return (1);
		}
		else
		{
			if (is_empty_line(line))
				return (error_msg("Empty line inside map"));
			if (!looks_like_map_block(line))
				return (error_msg("Invalid content after map start"));
			if (add_map_line(map_lines, line))
				return (1);
		}
		lines = lines->next;
	}
	if (!is_config_full(map))
		return (error_msg("Missing configuration"));
	if (!*map_lines)
		return (error_msg("Missing map"));
	return (0);
}
