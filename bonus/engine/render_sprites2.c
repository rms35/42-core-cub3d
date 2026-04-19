#include "../../includes/cub3d_bonus.h"

static int	compare_sprites(const void *a, const void *b)
{
	double	diff;

	diff = ((t_pair *)b)->dist - ((t_pair *)a)->dist;
	if (diff > 0)
		return (1);
	if (diff < 0)
		return (-1);
	return (0);
}

void	calculate_sprite_distances(t_win *win, t_pair *pairs)
{
	double	delta_x;
	double	delta_y;
	size_t	index;

	index = 0;
	while (index < win->n_sprites)
	{
		delta_x = win->player->pos_x - win->sprites[index].x;
		delta_y = win->player->pos_y - win->sprites[index].y;
		pairs[index].dist = (delta_x * delta_x) + (delta_y * delta_y);
		pairs[index].index = index;
		index++;
	}
}

void	sort_sprites(t_win *win)
{
	t_pair	*pairs;
	size_t	index;

	pairs = ft_calloc(win->n_sprites, sizeof(t_pair));
	if (!pairs)
		return ;
	calculate_sprite_distances(win, pairs);
	qsort(pairs, win->n_sprites, sizeof(t_pair), compare_sprites);
	index = 0;
	while (index < win->n_sprites)
	{
		win->sprite_order[index] = pairs[index].index;
		win->sprite_dist[index] = pairs[index].dist;
		index++;
	}
	free(pairs);
}

void	calculate_draw_params(t_win *win, t_sprite *sprite,
	t_sprite_draw *draw)
{
	draw->sprite_height = ft_abs((int)(HEIGHT / sprite->trans_y)) / 2;
	draw->draw_start_y = -draw->sprite_height / 2 + HEIGHT / 2
		+ win->player->pitch;
	if (draw->draw_start_y < 0)
		draw->draw_start_y = 0;
	draw->draw_end_y = draw->sprite_height / 2 + HEIGHT / 2
		+ win->player->pitch;
	if (draw->draw_end_y >= HEIGHT)
		draw->draw_end_y = HEIGHT - 1;
	draw->sprite_width = ft_abs((int)(HEIGHT / sprite->trans_y)) / 2;
	draw->sprite_screen_x = (int)((WIDTH / 2)
			* (1 + sprite->trans_x / sprite->trans_y));
	draw->draw_start_x = -draw->sprite_width / 2 + draw->sprite_screen_x;
	if (draw->draw_start_x < 0)
		draw->draw_start_x = 0;
	draw->draw_end_x = draw->sprite_width / 2 + draw->sprite_screen_x;
	if (draw->draw_end_x >= WIDTH)
		draw->draw_end_x = WIDTH - 1;
}

unsigned int	alpha_blend(unsigned int background, unsigned int foreground,
	float alpha)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;

	red = (unsigned int)((((background >> 16) & 0xFF) * (1.0 - alpha))
			+ (((foreground >> 16) & 0xFF) * alpha));
	green = (unsigned int)((((background >> 8) & 0xFF) * (1.0 - alpha))
			+ (((foreground >> 8) & 0xFF) * alpha));
	blue = (unsigned int)(((background & 0xFF) * (1.0 - alpha))
			+ ((foreground & 0xFF) * alpha));
	return ((red << 16) | (green << 8) | blue);
}