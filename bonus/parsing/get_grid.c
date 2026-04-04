/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_grid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 12:00:00 by rafael-m          #+#    #+#             */
/*   Updated: 2026/03/28 12:55:00 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

static	int check_chars(const char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("01FNSFEWV \n", line[i]))
			return (printf("%d\n", line[i]), write(2, "Error: Invalid map "
													  "char\n",
				25), 1);
		i++;
	}
	return (0);
}

static char	*gnl(const int fd)
{
	ssize_t	br;
	char	*line;
	char	*t;
	char	buffer;
	char	s_buf[2];

	br = 1;
	line = ft_strdup("");
	if (!line)
		return (NULL);
	s_buf[1] = '\0';
	while (br > 0)
	{
		br = read(fd, &buffer, 1);
		if (br == -1)
			return (free(line), write(2, "Error: read map file\n", 21), NULL);
		if (br == 0)
		{
			if (line[0] == '\0')
				return (free(line), NULL);
			return (line);
		}
		s_buf[0] = buffer;
		t = ft_strjoin(line, s_buf);
		free(line);
		if (!t)
			return (write(2, "Error: malloc\n", 14), NULL);
		line = t;
		if (buffer == '\n')
			return (line);
	}
	return (line);
}

int	get_grid(const char *file, t_map *map)
{
	char	*l;
	int		fd;
	size_t	i;

	map->grid = ft_calloc(map->width * map->height + 1, sizeof(char));
	fd = open(file, O_RDONLY);
	if (fd < 0 || !map->grid)
		return (write(2, "Error: Map loading\n", 19), 1);
	i = 0;
	l = gnl(fd);
	while (l)
	{
		if (i < map->height)
			ft_strncpy(map->grid + (i++ * map->width), l, ft_strlen(l));
		if (check_chars(l))
			return (free(l), 1);
		free(l);
		l = gnl(fd);
	}
	close(fd);
	if (validate_map(map))
	{
		return (1);
	}
	return (0);
}
