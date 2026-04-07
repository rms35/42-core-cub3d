/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:32:24 by rafael-m          #+#    #+#             */
/*   Updated: 2026/03/26 10:33:01 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static ssize_t	line_len(const int fd)
{
	char	buffer;
	ssize_t	br;
	ssize_t	len;

	br = 1;
	len = 0;
	while (br > 0)
	{
		br = read(fd, &buffer, 1);
		if (br == -1)
			return (write(2, "Error: reading map file\n", 25), -1);
		if (br == 0)
			return (len);
		len++;
		if (buffer == '\n')
			return (len);
	}
	return (-1);
}

static int	get_width_height(const char *file, t_map *map)
{
	ssize_t	len;
	int		fd;

	len = 1;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error: failed to open map file\n", 32), 0);
	while (len > 0)
	{
		len = line_len(fd);
		if (len < 0)
		{
			if (close(fd))
				write(2, "Error: closing map file\n", 25);
			return (0);
		}
		if ((size_t)len > map->width)
			map->width = len;
		map->height += 1;
	}
	if (close(fd))
		return (write(2, "Error: closing map file\n", 25), 0);
	return (1);
}

t_map	*parsing(const int argc, const char *argv)
{
	t_map	*map;
	size_t	len;

	if (argc != 2)
		return (write(2, "Error: invalid number of maps\n", 31), NULL);
	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		return (write(2, "Error: malloc\n", 15), NULL);
	len = ft_strlen(argv);
	if (ft_strncmp(&argv[len - 4], ".cub", 4))
		return (write(2, "Error: invalid map file extension\n", 35), free(map),
			NULL);
	if (!get_width_height(argv, map))
		return (free(map), NULL);
	get_grid(argv, map);
	return (map);
}