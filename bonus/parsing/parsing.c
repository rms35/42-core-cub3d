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
