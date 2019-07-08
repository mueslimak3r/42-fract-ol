#include "fractol.h"

static int	fdf_key_hook(int key, t_mlx *mlx)
{
	if (key == KEY_ESCAPE)
	{
		mlxdel(mlx);
		exit(0);
	}
	if (key == KEY_W)
		mlx->cam->scale *= 1.3;
	if (key == KEY_S)
	{
		if (mlx->cam->scale / 1.3 == 0)
			return (0);
		mlx->cam->scale /= 1.3;
	}
	if (key == KEY_I)
	{
		mlx->iterations += 1;
	}
	if (key == KEY_R)
	{
		if (mlx->iterations - 1 < 0)
			return (0);
		mlx->iterations -= 1;
	}
	mlx_clear_window(mlx->mlx, mlx->window);
	mlx_draw(mlx);
	mlx_string_put(mlx->mlx, mlx->window, 10, WIN_HEIGHT - 30, WHITE, "ESC: close");
	return (0);
}

void		start(t_mlx *mlx)
{
	if (ft_strcmp(mlx->type, "sierpinski") == 0)
		mlx->iterations = 10;
	if (ft_strcmp(mlx->type, "mandelbrot") == 0)
		mlx->iterations = 100;
    mlx_draw(mlx);
	mlx_hook(mlx->window, 2, 5, fdf_key_hook, mlx);
	mlx_string_put(mlx->mlx, mlx->window, 10, WIN_HEIGHT - 30, WHITE, "ESC: close");
	mlx_loop(mlx->mlx);
}
