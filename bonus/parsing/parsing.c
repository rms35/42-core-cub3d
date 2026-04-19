/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by almorene          #+#    #+#             */
/*   Updated: 2026/04/19 15:40:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static char	*read_line_helper(int fd, char *line, char *tmp)
{
	ssize_t	bytes_read;
	char	buffer;
	char	*joined;

	bytes_read = read(fd, &buffer, 1);
	while (bytes_read > 0)
	{
		tmp[0] = buffer;
		joined = ft_strjoin(line, tmp);
		free(line);
		if (!joined)
			return (NULL);
		line = joined;
		if (buffer == '\n')
			break ;
		bytes_read = read(fd, &buffer, 1);
	}
	if (bytes_read < 0 || (bytes_read == 0 && line[0] == '\0'))
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static char	*read_line(int fd)
{
	char	*line;
	char	tmp[2];

	line = ft_strdup("");
	if (!line)
		return (NULL);
	tmp[1] = '\0';
	return (read_line_helper(fd, line, tmp));
}

static void	free_lines(t_list **lines)
{
	ft_lstclear(lines, free);
}

static int	read_cub_file(char *path, t_list **lines)
{
	int		fd;
	char	*line;
	t_list	*node;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (error_msg("Could not open map file"));
	line = read_line(fd);
	while (line)
	{
		node = ft_lstnew(line);
		if (!node)
		{
			close(fd);
			free(line);
			free_lines(lines);
			return (error_msg("Memory allocation failed"));
		}
		ft_lstadd_back(lines, node);
		line = read_line(fd);
	}
	close(fd);
	if (!*lines)
		return (error_msg("Empty map file"));
	return (0);
}

static void	free_map_config(t_map *map)
{
	if (!map)
		return ;
	free(map->grid);
	free(map->no_path);
	free(map->so_path);
	free(map->we_path);
	free(map->ea_path);
	free(map);
}

static int	check_map_path(char *path)
{
	size_t	len;

	if (!path)
		return (error_msg("Missing map path"));
	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".cub", 4))
		return (error_msg("Invalid map extension"));
	return (0);
}

static t_map	*finish_parsing(t_map *map, t_list *lines)
{
	t_list	*map_lines;

	map_lines = NULL;
	if (parse_config_lines(lines, map, &map_lines)
		|| build_grid(map, map_lines) || validate_map(map))
	{
		free_lines(&lines);
		free_lines(&map_lines);
		free_map_config(map);
		return (NULL);
	}
	free_lines(&lines);
	free_lines(&map_lines);
	return (map);
}

t_map	*parsing(int argc, char **argv)
{
	t_map	*map;
	t_list	*lines;

	if (argc != 2)
	{
		error_msg("Usage: ./cub3D_bonus <map.cub>");
		return (NULL);
	}
	if (check_map_path(argv[1]))
		return (NULL);
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
	{
		error_msg("Memory allocation failed");
		return (NULL);
	}
	map->floor_color = -1;
	map->ceil_color = -1;
	lines = NULL;
	if (read_cub_file(argv[1], &lines))
	{
		free(map);
		return (NULL);
	}
	return (finish_parsing(map, lines));
}
