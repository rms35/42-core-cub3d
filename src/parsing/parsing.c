/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almorene <almorene@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 00:00:00 by almorene          #+#    #+#             */
/*   Updated: 2026/04/12 00:00:00 by almorene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static char	*read_line(int fd)
{
	ssize_t	bytes_read;
	char	buffer;
	char	tmp[2];
	char	*line;
	char	*joined;

	line = ft_strdup("");
	if (!line)
		return (NULL);
	tmp[1] = '\0';
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, &buffer, 1);
		if (bytes_read < 0)
			return (free(line), NULL);
		if (bytes_read == 0)
			return (line[0] == '\0' ? (free(line), NULL) : line);
		tmp[0] = buffer;
		joined = ft_strjoin(line, tmp);
		free(line);
		if (!joined)
			return (NULL);
		line = joined;
		if (buffer == '\n')
			break ;
	}
	return (line);
}

static void	free_lines(t_list **lines)
{
	ft_lstclear(lines, free);
}

void	free_map(t_map *map)
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

static int	read_cub_file(const char *path, t_list **lines)
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
			return (close(fd), free(line), free_lines(lines),
				error_msg("Memory allocation failed"));
		ft_lstadd_back(lines, node);
		line = read_line(fd);
	}
	close(fd);
	if (!*lines)
		return (error_msg("Empty map file"));
	return (0);
}

static int	check_map_path(const char *path)
{
	size_t	len;

	if (!path)
		return (error_msg("Missing map path"));
	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".cub", 4))
		return (error_msg("Invalid map extension"));
	return (0);
}

int	parse_map_file(t_map **map, int argc, char **argv)
{
	t_list	*lines;
	t_list	*map_lines;

	if (argc != 2)
		return (error_msg("Usage: ./cub3D <map.cub>"));
	if (check_map_path(argv[1]))
		return (1);
	*map = ft_calloc(1, sizeof(t_map));
	if (!*map)
		return (error_msg("Memory allocation failed"));
	(*map)->floor_color = -1;
	(*map)->ceil_color = -1;
	lines = NULL;
	map_lines = NULL;
	if (read_cub_file(argv[1], &lines))
		return (free_map(*map), *map = NULL, 1);
	if (parse_config_lines(lines, *map, &map_lines)
		|| build_grid(*map, map_lines)
		|| validate_map(*map))
	{
		free_lines(&lines);
		free_lines(&map_lines);
		return (free_map(*map), *map = NULL, 1);
	}
	free_lines(&lines);
	free_lines(&map_lines);
	return (0);
}
