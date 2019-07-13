#include "fractol.h"

int		hook_mouse_press(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	if (y < 0)
		return (0);
	if (button == 1)
	{
		mlx->mouse->clicked = true;
	}
	return (0);
}

int		hook_mouse_unpress(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	(void)y;
	if (button == 1)
		mlx->mouse->clicked = false;
	return (0);
}

int		hook_mousemove(int x, int y, t_mlx *mlx)
{
	mlx->mouse->lastx = mlx->mouse->x;
	mlx->mouse->lasty = mlx->mouse->y;
	mlx->mouse->x = x;
	mlx->mouse->y = y; 
	if (mlx->mouse->clicked)
		mlx->cam->scale *= 1.3;
	if (mlx->mouse->clicked)
	{
		mlx_draw(mlx);
		mlx->mouse->clicked = false;
	}
	else
		mlx_draw(mlx);
	return (0);
}

static int	fdf_key_hook(int key, t_mlx *mlx)
{
	if (key == KEY_ESCAPE)
	{
		mlxdel(mlx);
		exit(0);
	}
	if (key == KEY_W || key == KEY_PAD_1)
	{
		mlx->cam->scale *= 1.3;
	}
	if (key == KEY_S || key == KEY_PAD_2)
	{
		if (mlx->cam->scale * 0.6 <= 0)
			return (0);
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
	mlx_draw(mlx);
	return (0);
}

void		start(t_mlx *mlx)
{
	if (ft_strcmp(mlx->type, "sierpinski") == 0)
		mlx->iterations = 10;
	if (ft_strcmp(mlx->type, "mandelbrot") == 0)
		mlx->iterations = 50;
	if (ft_strcmp(mlx->type, "julia") == 0)
		mlx->iterations = 50;
    mlx_draw(mlx);
	mlx_hook(mlx->window, 4, 0, hook_mouse_unpress, mlx);
	mlx_hook(mlx->window, 5, 0, hook_mouse_press, mlx);
	mlx_hook(mlx->window, 6, 0, hook_mousemove, mlx);
	mlx_hook(mlx->window, 2, 5, fdf_key_hook, mlx);
	mlx_loop(mlx->mlx);
}
