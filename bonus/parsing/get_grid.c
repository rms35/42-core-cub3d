#include "../../includes/cub3d_bonus.h"

static char	*gnl(const int fd)
{
	ssize_t	br;
	char	*line;
	char	*t;
	char	buffer;

	br = 1;
	line = NULL;
	while (br > 0)
	{
		br = read(fd, &buffer, 1);
		if (br == -1)
		{
			free(line);
			return (write(2, "Error: reading map file\n", 25), NULL);
		}
		if (br == 0)
			return (line);
		t = ft_strjoin(line, &buffer);
		free(line);
		if (!t)
			return (write(2, "Error: malloc\n", 14), NULL);
		line = t;
		if (buffer == '\n')
			return (line);
	}
	return (NULL);
}

int	get_grid(const char *file, t_map *map)
{
	char	*line;
	int		fd;
	size_t	pos;

	map->grid = ft_calloc(map->width * map->height, sizeof(char));
	if (!map->grid)
		return (write(2, "Error: malloc\n", 14), 1);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (write(2, "Error: failed to open map file\n", 32), 1);
	pos = 0;
	while ((line = gnl(fd)))
	{
		ft_strncpy(map->grid + pos, line, ft_strlen(line));
		pos += map->width;
		free(line);
	}
	if (close((fd)))
		return (write(2, "Error: closing map file\n", 25), 1);
	return (0);
}