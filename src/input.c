#include "fractol.h"

static int	fdf_key_hook(int key, t_mlx *mlx)
{
	if (key == KEY_ESCAPE)
	{
		mlxdel(mlx);
		exit(0);
	}
	if (key == KEY_W || key == KEY_PAD_1)
	{
		mlx->cam->x += (((WIN_WIDTH * mlx->cam->scale) * 1.3) - (WIN_WIDTH * mlx->cam->scale)) / ((WIN_WIDTH * mlx->cam->scale) / mlx->cam->x);
		mlx->cam->y += (((WIN_HEIGHT * mlx->cam->scale) * 1.3) - (WIN_HEIGHT * mlx->cam->scale)) / ((WIN_HEIGHT * mlx->cam->scale) / mlx->cam->y);
		mlx->cam->scale *= 1.3;
	}
	if (key == KEY_S || key == KEY_PAD_2)
	{
		if (mlx->cam->scale * 0.6 <= 0)
			return (0);
		mlx->cam->x -= ((WIN_WIDTH * mlx->cam->scale) - ((WIN_WIDTH * mlx->cam->scale) * 0.6)) / ((WIN_WIDTH * mlx->cam->scale) / mlx->cam->x);
		mlx->cam->y -= ((WIN_HEIGHT * mlx->cam->scale) - ((WIN_HEIGHT * mlx->cam->scale) * 0.6)) / ((WIN_HEIGHT * mlx->cam->scale) / mlx->cam->y);;
		mlx->cam->scale *= 0.6;
	}
	if (key == KEY_I || key == KEY_PAD_4)
		mlx->iterations += ft_strcmp(mlx->type, "mandelbrot") == 0 ? 25 : 1;
	if (key == KEY_R || key == KEY_PAD_5)
	{
		if (mlx->iterations - 1 < 0)
			return (0);
		mlx->iterations -= 1;
	}
	if (key == KEY_BACKSPACE)
	{
		mlx->cam->x = 0;
		mlx->cam->y = 0;
		mlx->cam->scale = 1.0;
	}
	if (key == KEY_UP || key == KEY_DOWN)
		mlx->cam->y += key == KEY_UP ? -50 : 50;
	if (key == KEY_LEFT || key == KEY_RIGHT)
		mlx->cam->x += key == KEY_RIGHT ? 50 : -50;
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
		mlx->iterations = 50;
    mlx_draw(mlx);
	mlx_hook(mlx->window, 2, 5, fdf_key_hook, mlx);
	mlx_string_put(mlx->mlx, mlx->window, 10, WIN_HEIGHT - 30, WHITE, "ESC: close");
	mlx_loop(mlx->mlx);
}
