/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael-m <rafael-m@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 10:32:24 by rafael-m          #+#    #+#             */
/*   Updated: 2026/04/02 14:15:00 by rafael-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d_bonus.h"

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
			return (free(line), NULL);
		if (br == 0)
			return (line[0] == '\0' ? (free(line), NULL) : line);
		s_buf[0] = buffer;
		t = ft_strjoin(line, s_buf);
		free(line);
		if (!t)
			return (NULL);
		line = t;
		if (buffer == '\n')
			return (line);
	}
	return (line);
}

static int	extract_data(const int fd, t_map *map, t_list **grid_lst)
{
	char	*line;
	int		is_config;

	line = gnl(fd);
	while (line)
	{
		if (!is_config_full(map))
		{
			is_config = parse_line_config(line, map);
			if (is_config == -1)
				return (free(line), -1);
		}
		else if (line[0] != '\n' || *grid_lst)
			ft_lstadd_back(grid_lst, ft_lstnew(ft_strdup(line)));
		free(line);
		line = gnl(fd);
	}
	return (0);
}

static void	process_grid(t_map *map, t_list *grid_lst)
{
	t_list	*curr;
	size_t	len;
	int		i;

	curr = grid_lst;
	map->height = ft_lstsize(grid_lst);
	while (curr)
	{
		len = ft_strlen((char *)curr->content);
		if (len > map->width)
			map->width = len;
		curr = curr->next;
	}
	map->grid = ft_calloc(map->width * map->height + 1, sizeof(char));
	if (!map->grid)
		return ;
	curr = grid_lst;
	i = 0;
	while (curr)
	{
		ft_strncpy(map->grid + (i++ * map->width), (char *)curr->content, ft_strlen((char *)curr->content));
		curr = curr->next;
	}
}

t_map	*parsing(const int argc, const char *argv)
{
	t_map	*map;
	t_list	*grid_lst;
	int		fd;

	grid_lst = NULL;
	if (argc != 2)
		return (write(2, "Error: invalid number of maps\n", 31), NULL);
	map = ft_calloc(sizeof(t_map), 1);
	if (!map)
		return (NULL);
	map->floor_color = -1;
	map->ceil_color = -1;
	if (ft_strncmp(&argv[ft_strlen(argv) - 4], ".cub", 4))
		return (write(2, "Error: invalid map file extension\n", 35), free(map), NULL);
	fd = open(argv, O_RDONLY);
	if (fd < 0)
		return (free(map), NULL);
	if (extract_data(fd, map, &grid_lst) == -1)
		return (ft_lstclear(&grid_lst, free), free(map), NULL);
	close(fd);
	if (!is_config_full(map))
		return (ft_lstclear(&grid_lst, free), free(map), NULL);
	process_grid(map, grid_lst);
	ft_lstclear(&grid_lst, free);
	if (validate_map(map))
		return (free(map->grid), free(map), NULL);
	return (map);
}
