#include "fractol.h"



static int	ft_abs(int n)
{
	return ((n > 0) ? n : (n * -1));
}

int         colors(int i)
{
    int colors[3] = { RED, GREEN, BLUE };
    return(colors[i % 3]);
}

void        dda(t_mlx *mlx, t_vect_2 start, t_vect_2 end, int it)
{
	int	dx;
	int	dy;
	int	steps;
	int	i;

	dx = (int)end.x - (int)start.x;
	dy = (int)end.y - (int)start.y;
	steps = ft_abs(dx) > ft_abs(dy) ? ft_abs(dx) : ft_abs(dy);
	i = 0;
	while (i <= steps)
	{
        if (i == (steps / 2) - 1)
            end = (t_vect_2){ start.x, start.y };
        image_set_pixel(mlx->image, start.x, start.y, colors(it));
		start.x += dx / (float)steps;
		start.y += dy / (float)steps;
		i++;
	}
}

void                fractal_check_print(t_mlx *mlx, int x, int y, int it)
{
    if (x >= 0 && y <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT)
		image_set_pixel(mlx->image, x, y, colors(it));
}

void				fractal_init(t_mlx *mlx, void* (*fractal)(void *))
{
	pthread_t       thread[4];
	if (pthread_mutex_init(&g_lock, NULL) != 0)
        printf("Mutex initialization failed.\n");
	double xsize = WIN_WIDTH * mlx->cam->scale;
	double ysize = WIN_HEIGHT * mlx->cam->scale;// * 30;
	t_cam *cam = mlx->cam;
    for (int i = 0; i < 4; i++)
    {
		t_fractal_args args;// = malloc(sizeof(t_fractal_args));
		if (i == 0)
			args = ((t_fractal_args){ xsize, ysize, 0, 0, cam->x, cam->y, cam->x + (WIN_WIDTH / 2), cam->y + (WIN_HEIGHT / 2), mlx, });
		if (i == 1)
			args = ((t_fractal_args){ xsize, ysize, WIN_WIDTH / 2, 0, cam->x + (WIN_WIDTH / 2), cam->y, cam->x + WIN_WIDTH, cam->y + (WIN_HEIGHT / 2), mlx });
		if (i == 2)
			args = ((t_fractal_args){ xsize, ysize, WIN_WIDTH / 2, WIN_HEIGHT / 2, cam->x + (WIN_WIDTH / 2), cam->y + (WIN_HEIGHT / 2), cam->x + WIN_WIDTH, cam->y + WIN_HEIGHT, mlx });
		if (i == 3)
			args = ((t_fractal_args){ xsize, ysize, 0, WIN_HEIGHT / 2, cam->x, cam->y + (WIN_HEIGHT / 2), cam->x + (WIN_WIDTH / 2), cam->y + WIN_HEIGHT, mlx });
		pthread_create(&thread[i], NULL, fractal, &args);
		pthread_join(thread[i], NULL);
	}
}

void				mlx_draw(t_mlx *mlx)
{
    bool             valid;

    valid = false;
    clear_image(mlx->image);
	mlx_clear_window(mlx->mlx, mlx->window);
    if (ft_strcmp(mlx->type, "sierpinski") == 0)
    {
        sierpinski_init(mlx);
        valid = true;
    }
    if (ft_strcmp(mlx->type, "mandelbrot") == 0)
    {
        fractal_init(mlx, mandelbrot);
        valid = true;
    }
	if (ft_strcmp(mlx->type, "julia") == 0)
    {
		//t_fractal_args args;
		//args = ((t_fractal_args){ WIN_WIDTH, WIN_HEIGHT, 0, 0, mlx->cam->x, mlx->cam->y, WIN_WIDTH, WIN_HEIGHT, mlx });
        //julia(&args);
		fractal_init(mlx, julia);
        valid = true;
    }
	mlx_string_put(mlx->mlx, mlx->window, 10, WIN_HEIGHT - 30, WHITE, "ESC: close");
    if (valid == true)
        mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
    else
        mlx_string_put(mlx->mlx, mlx->window, WIN_WIDTH / 2 - 10, 10, WHITE, "bad selection");
}