#include "fractol.h"

static int	fdf_key_hook(int key, t_mlx *mlx)
{
	if (key == KEY_ESCAPE)
	{
		mlxdel(mlx);
		exit(0);
	}
	mlx_clear_window(mlx->mlx, mlx->window);
	mlx_draw(mlx);
	mlx_string_put(mlx->mlx, mlx->window, 10, WIN_HEIGHT - 30, WHITE, "ESC: close");
	return (0);
}

void		start(t_mlx *mlx)
{
    mlx_draw(mlx);
	mlx_hook(mlx->window, 2, 5, fdf_key_hook, mlx);
	mlx_string_put(mlx->mlx, mlx->window, 10, WIN_HEIGHT - 30, WHITE, "ESC: close");
	mlx_loop(mlx->mlx);
}
