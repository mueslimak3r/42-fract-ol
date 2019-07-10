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
	// Store current x and y values into last x and y values
	mlx->mouse->lastx = mlx->mouse->x;
	mlx->mouse->lasty = mlx->mouse->y;
	// Store parameters into current x and y values
	mlx->mouse->x = x;
	mlx->mouse->y = y;
	// Shifts the camera view if mouse is held down 
	if (mlx->mouse->clicked)
	{
		// Shifts the camera view
		mlx->cam->x = (x - (WIN_WIDTH / 2));
		mlx->cam->x = (y - (WIN_HEIGHT / 2));
		mlx->cam->x += (((WIN_WIDTH * mlx->cam->scale) * 1.3) - (WIN_WIDTH * mlx->cam->scale)) / ((WIN_WIDTH * mlx->cam->scale) / mlx->cam->x);
		mlx->cam->y += (((WIN_HEIGHT * mlx->cam->scale) * 1.3) - (WIN_HEIGHT * mlx->cam->scale)) / ((WIN_HEIGHT * mlx->cam->scale) / mlx->cam->y);
		mlx->cam->scale *= 1.3;
	}
	// If the mouse is down, continue rendering
	if (mlx->mouse->clicked)
	{
		mlx_draw(mlx);
		mlx->mouse->clicked = false;
	}
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
		/*

		int newx = mlx->cam->x + (WIN_WIDTH / 2) * 1.3;
		int newy;

		*/
		//mlx->cam->x += (mlx->cam->x + mlx->cam->x + (WIN_WIDTH /2)) * 0.5f;
		//mlx->cam->y += (mlx->cam->y + mlx->cam->y + (WIN_HEIGHT /2)) * 0.5f;
		mlx->cam->x += (mlx->cam->x + mlx->cam->x + (WIN_WIDTH /2)) * 0.5f;
		mlx->cam->y += (mlx->cam->y + mlx->cam->y + (WIN_HEIGHT /2)) * 0.5f;
		//mlx->cam->x += (((WIN_WIDTH * mlx->cam->scale) + ((WIN_WIDTH * mlx->cam->scale) * 1.3)) * 0.5f) / ((WIN_WIDTH * mlx->cam->scale) / mlx->cam->x);
		//			+= (((WIN_HEIGHT * mlx->cam->scale) + ((WIN_HEIGHT * mlx->cam->scale) * 1.3)) * 0.5f) / ((WIN_HEIGHT * mlx->cam->scale) / mlx->cam->y);
		
		//mlx->cam->x -= (WIN_WIDTH / 2);
		//mlx->cam->y -= (WIN_HEIGHT / 2);
		//mlx->cam->x += (((WIN_WIDTH * mlx->cam->scale) * 1.3) - (WIN_WIDTH * mlx->cam->scale)) / ((WIN_WIDTH * mlx->cam->scale) / mlx->cam->x);
		//mlx->cam->y += (((WIN_HEIGHT * mlx->cam->scale) * 1.3) - (WIN_HEIGHT * mlx->cam->scale)) / ((WIN_HEIGHT * mlx->cam->scale) / mlx->cam->y);
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
	mlx_draw(mlx);
	return (0);
}

void		start(t_mlx *mlx)
{
	if (ft_strcmp(mlx->type, "sierpinski") == 0)
		mlx->iterations = 10;
	if (ft_strcmp(mlx->type, "mandelbrot") == 0)
		mlx->iterations = 50;
    mlx_draw(mlx);
	mlx_hook(mlx->window, 4, 0, hook_mouse_unpress, mlx);
	mlx_hook(mlx->window, 5, 0, hook_mouse_press, mlx);
	mlx_hook(mlx->window, 6, 0, hook_mousemove, mlx);
	mlx_hook(mlx->window, 2, 5, fdf_key_hook, mlx);
	mlx_loop(mlx->mlx);
}
