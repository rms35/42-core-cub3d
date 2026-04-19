/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafael <rafael@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:56:33 by rafael            #+#    #+#             */
/*   Updated: 2026/04/19 16:45:36 by rafael           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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
		return (free(path), error_msg("Missing texture path"));
	if (!is_valid_texture_path(path))
		return (free(path), error_msg("Invalid texture path"));
	*slot = path;
	return (0);
}

int	looks_like_map_block(char *line)
{
	int	has_non_space;

	line = skip_spaces(line);
	if (!*line || *line == '\n')
		return (0);
	has_non_space = 0;
	while (*line && *line != '\n')
	{
		if (*line != ' ')
			has_non_space = 1;
		line++;
	}
	return (has_non_space);
}

int	is_valid_texture_path(const char *path)
{
	size_t			len;
	struct stat		path_stat;

	len = ft_strlen(path);
	if (len < 5 || ft_strncmp(path + len - 4, ".xpm", 4) != 0)
		return (0);
	if (stat(path, &path_stat) != 0)
		return (0);
	if (S_ISDIR(path_stat.st_mode))
		return (0);
	if (access(path, R_OK) != 0)
		return (0);
	return (1);
}
