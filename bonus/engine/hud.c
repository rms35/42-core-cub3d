#include "../../includes/cub3d_bonus.h"

void	my_mlx_pixel_put(const t_img *img, const int x, const int y, const int
	color)
{
	char	*dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void	set_cell(const t_img *img, const size_t x, const size_t y, const int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINI_FACTOR)
	{
		j = 0;
		while (j < MINI_FACTOR)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i ++;
	}
}

void	set_floor(const t_img *img, const size_t x, const size_t y, const int
	color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINI_FACTOR)
	{
		j = 0;
		while (j < MINI_FACTOR)
		{
			if (j % 2)
				my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i ++;
	}
}

void	set_player(const t_img *img, const size_t x, const size_t y, const int
	color)
{
	int	i;
	int	j;

	i = 0;
	while (i < PLYR_FACTOR)
	{
		j = 0;
		while (j < PLYR_FACTOR)
		{
			my_mlx_pixel_put(img, x + i, y + j, color);
			j++;
		}
		i ++;
	}
}

static void	render_minimap(const t_map *map, const t_img *img, const t_win *win)
{
	size_t	i;
	size_t	total;
	size_t	x;
	size_t	y;

	total = map->width * map->height;
	i = 0;
	while (i < total)
	{
		x = i % map->width;
		y = i / map->width;
		if (win->map->grid[i] != ' ')
			set_floor(img, x * MINI_FACTOR, y * MINI_FACTOR, win->minilu[(int)
				map->grid[i]]);
		i++;
	}
	set_player(img, win->player->pos_x * MINI_FACTOR, win->player->pos_y *
		MINI_FACTOR,
		0x00FF0000);
}

void	render_hud(const t_win *win)
{
	render_minimap(win->map, win->img, win);
}