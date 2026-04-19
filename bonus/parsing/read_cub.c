/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 17:10:00 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 16:25:00 by rafael           ###   ########.fr       */
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

void	free_lines(t_list **lines)
{
	ft_lstclear(lines, free);
}

int	read_cub_file(const char *path, t_list **lines)
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
