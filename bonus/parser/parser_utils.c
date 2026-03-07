/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 22:50:00 by rafael            #+#    #+#             */
/*   Updated: 2026/03/06 22:50:00 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	if (map->grid)
		free(map->grid);
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->we_path)
		free(map->we_path);
	if (map->ea_path)
		free(map->ea_path);
	free(map);
}

char	*skip_spaces(char *str)
{
	if (!str)
		return (NULL);
	while (*str && ft_isspace(*str))
		str++;
	return (str);
}

char	*get_next_line_parser(int fd)
{
	char	*line;
	char	buf[2];
	int		res;

	line = ft_strdup("");
	res = read(fd, buf, 1);
	while (res > 0)
	{
		buf[1] = '\0';
		line = ft_strjoin(line, buf);
		if (buf[0] == '\n')
			break ;
		res = read(fd, buf, 1);
	}
	if (res <= 0 && ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}
