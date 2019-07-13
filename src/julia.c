#include "fractol.h"

static int		calc(t_fractal_args *r, double x, double y)
{
	int			i;
	long double	temp;

	x = ((4.0 * x / r->xsize - 2.0) / r->mlx->cam->scale);
	y = ((4.0 * y / r->ysize - 2.0) / r->mlx->cam->scale);
	i = 0;
	while (x * x + y * y < 4.0 && i < r->mlx->iterations)
	{
		temp = x * x - y * y + (r->mlx->mouse->x * 4.0 / r->xsize - 2);
		y = 2 * x * y + (r->mlx->mouse->y * 4.0 / r->ysize - 2);
		x = temp;
		i++;
	}
	return (i);
}

void            *julia(void *args)
{
	t_fractal_args *r = args;
	pthread_mutex_lock(&g_lock);
	int sy= r->screeny;
	for(double y=r->yoffset;y<r->yend;y++)
	{
		int sx = r->screenx;
		for(double x=r->xoffset; x<r->xend; x++)
      	{
          	int it= calc(args, x, y);
            if (it < r->mlx->iterations)
                fractal_check_print(r->mlx, sx, sy, it);
			sx++;
		}
		sy++;
  	}
	pthread_mutex_unlock(&g_lock);
	pthread_exit(NULL);
	return (0);
}

