/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 22:40:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 23:15:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 5)
		return (0);
	if (ft_strcmp(file + len - 4, ".cub") != 0)
		return (0);
	return (1);
}

static t_map	*init_map_struct(int fd)
{
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (!map)
		return (close(fd), NULL);
	ft_memset(map, 0, sizeof(t_map));
	return (map);
}

static int	parse_all(t_map *map, int fd)
{
	if (!parse_elements(map, fd))
	{
		write(2, "Error: Invalid or missing configuration elements\n", 49);
		return (0);
	}
	if (!parse_grid(map, fd))
	{
		write(2, "Error: Invalid or missing map grid\n", 35);
		return (0);
	}
	if (!validate_map(map))
		return (0);
	return (1);
}

t_map	*parse_map(char *file)
{
	int		fd;
	t_map	*map;

	if (!check_extension(file))
		return (write(2, "Error: Invalid file extension\n", 30), NULL);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (perror("Error"), NULL);
	map = init_map_struct(fd);
	if (!map)
		return (NULL);
	if (!parse_all(map, fd))
	{
		free_map(map);
		close(fd);
		return (NULL);
	}
	close(fd);
	return (map);
}
