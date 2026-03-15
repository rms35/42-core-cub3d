#include "../includes/cub3d_bonus.h"
# define P1_FOV 1.7

void	init_ray1(t_ray *ray, const t_player *player, const int x)
{
	double cam_segm;

	cam_segm = 2 * x / (double)WIDTH - 1;
	ray->dir_x = player->dir_x + player->camp_x * cam_segm;
	ray->dir_y = player->dir_y + player->camp_y * cam_segm;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
	ray->delta_dist_x = fabs(1 / ray->dir_x);
	ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit = 0;
	ray->step_x = 1 - 2 * (ray->dir_x < 0);
	if (ray->dir_x < 0)
		ray->side_dist_x = (player->pos_x - ray->map_x)
			* ray->delta_dist_x;
	else
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x)
			* ray->delta_dist_x;
	ray->step_y = 1 - 2 * (ray->dir_y < 0);
	if (ray->dir_y < 0)
		ray->side_dist_y = (player->pos_y - ray->map_y)
			* ray->delta_dist_y;
	else
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y)
			* ray->delta_dist_y;
}

int	main()
{
	t_player	player;
	t_img		img;
	t_win		win;
	t_map		*map;

	ft_bzero(&win, sizeof(t_win));
	map = get_mock_map();
	init_player(&player, map, P1_FOV);
	win.player = &player;
	win.map = map;
	win.img = &img;
	setup_mlx(&win, win.img);
	render_frame(&win);
	mlx_put_image_to_window(win.mlxptr, win.winptr, img.img, 0, 0);
	mlx_loop_hook(win.mlxptr, game_loop, &win);
	mlx_loop(win.mlxptr);
}