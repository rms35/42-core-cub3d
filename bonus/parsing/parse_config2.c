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

char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

int	parse_channel(const char **str, int *value)
{
	int	result;

	*str = skip_spaces((char *)*str);
	if (!ft_isdigit(**str))
		return (1);
	result = 0;
	while (ft_isdigit(**str))
	{
		result = (result * 10) + (**str - '0');
		if (result > 255)
			return (1);
		(*str)++;
	}
	*str = skip_spaces((char *)*str);
	*value = result;
	return (0);
}

int	add_map_line(t_list **map_lines, const char *line)
{
	t_list	*node;
	char	*content;

	content = ft_strdup(line);
	if (!content)
		return (error_msg("Memory allocation failed"));
	node = ft_lstnew(content);
	if (!node)
	{
		free(content);
		return (error_msg("Memory allocation failed"));
	}
	ft_lstadd_back(map_lines, node);
	return (0);
}

static int	is_valid_texture_path(const char *path)
{
	size_t		len;
	struct stat	path_stat;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strncmp(path + len - 4, ".xpm", 4) != 0
		&& ft_strncmp(path + len - 4, ".png", 4) != 0)
		return (0);
	if (stat(path, &path_stat) != 0)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
		return (0);
	if (access(path, R_OK) != 0)
		return (0);
	return (1);
}

int	set_texture_path(char **slot, char *line)
{
	char	*path;

	if (*slot)
		return (error_msg("Duplicate texture identifier"));
	line = skip_spaces(line);
	if (!*line || *line == '\n')
		return (error_msg("Missing texture path"));
	path = ft_strtrim(line, " \n");
	if (!path || !*path)
	{
		free(path);
		return (error_msg("Missing texture path"));
	}
	if (!is_valid_texture_path(path))
	{
		free(path);
		return (error_msg("Invalid texture path"));
	}
	*slot = path;
	return (0);
}
