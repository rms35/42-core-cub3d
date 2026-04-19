#include "../../includes/cub3d.h"

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

int	is_map_line(char *line)
{
	int	has_map_char;

	line = skip_spaces(line);
	if (!*line || *line == '\n')
		return (0);
	has_map_char = 0;
	while (*line && *line != '\n')
	{
		if (*line != ' ' && *line != '0' && *line != '1'
			&& !ft_strchr(PLYR_DIR, *line))
			return (0);
		if (*line == '0' || *line == '1' || ft_strchr(PLYR_DIR, *line))
			has_map_char = 1;
		line++;
	}
	return (has_map_char);
}