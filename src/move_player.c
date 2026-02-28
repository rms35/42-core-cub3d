#include "../includes/cub3d.h"

int	move_up(t_map *map)
{
	int	new_pos;

	new_pos = map->player_pos - map->width;
	// printf("new_pos = %d\n", new_pos);
	if (new_pos > 0 && map->grid[new_pos] != '1')
	{
		map->grid[map->player_pos] = '0';
		map->grid[new_pos] = 'N';
		map->player_pos = new_pos;
		return (1);
	}
	check_map(map);
	return (0);
}

int	move_down(t_map *map)
{
	int	new_pos;

	new_pos = map->player_pos + map->width;
	if (map->grid[new_pos] != '1')
	{
		map->grid[map->player_pos] = '0';
		map->grid[new_pos] = 'N';
		map->player_pos = new_pos;
		return (1);
	}
	check_map(map);
	return (0);
}

int	move_left(t_map *map)
{
	int	new_pos;

	new_pos = map->player_pos - 1;
	if (map->grid[new_pos] != '1')
	{
		map->grid[map->player_pos] = '0';
		map->grid[new_pos] = 'N';
		map->player_pos = new_pos;
		return (1);
	}
	check_map(map);
	return (0);
}

int	move_right(t_map *map)
{
	int	new_pos;

	new_pos = map->player_pos + 1;
	if (map->grid[new_pos] != '1')
	{
		map->grid[map->player_pos] = '0';
		map->grid[new_pos] = 'N';
		map->player_pos = new_pos;
		return (1);
	}
	check_map(map);
	return (0);
}