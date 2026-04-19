#include "../../includes/cub3d_bonus.h"

#ifdef LINUX

static void	destroy_mlx_display(t_win *win)
{
	if (win->mlxptr)
	{
		mlx_destroy_display(win->mlxptr);
		free(win->mlxptr);
	}
}

#else

static void	destroy_mlx_display(t_win *win)
{
	if (win->mlxptr)
		free(win->mlxptr);
}

#endif

void	cleanup_mlx(t_win *win)
{
	mlx_mouse_show(win->mlxptr, win->winptr);
	if (win->img && win->img->img)
		mlx_destroy_image(win->mlxptr, win->img->img);
	if (win->winptr)
		mlx_destroy_window(win->mlxptr, win->winptr);
	destroy_mlx_display(win);
}

void	cleanup_textures(t_win *win)
{
	size_t	index;

	index = 0;
	if (win->door && win->door->img)
		mlx_destroy_image(win->mlxptr, win->door->img);
	free(win->door);
	while (index < N_FIRES)
	{
		if (win->fire[index].img)
			mlx_destroy_image(win->mlxptr, win->fire[index].img);
		index++;
	}
	index = 0;
	while (index < N_TEX)
	{
		if (win->textures[index].img)
			mlx_destroy_image(win->mlxptr, win->textures[index].img);
		index++;
	}
}