#include "fractol.h"

int				m_calc(t_mlx *mlx, double re, double im)
{
	double zr = re;
	double zi = im;
	int it = 0;
	while (it < mlx->iterations)
	{
		double a=zr*zr;
		double b=zi*zi;
        if(a+b>4.0)
			break;
        zi=2*zr*zi+im;
		zr=a-b+re;
		it++;
	}
	return (it);
}

void            *mandelbrot(void *args)
{
	t_fractal_args *r = args;

	pthread_mutex_lock(&g_lock);
  	double StepX = (1.0 - (-2.0)) / r->xsize;
  	double StepY = (1.0 - (-1.0)) / r->ysize;
	double y = r->yoffset;
	while (y++ < r->yend)
	{
		int sx = r->screenx;
		double x = r->xoffset;
		while (x++ < r->xend)
      	{
          	int it;
        	it = m_calc(r->mlx, (-2.0 + StepX * x), (-1.0 + StepY * y));
			fractal_check_print(r->mlx, sx, r->screeny, it);
			sx++;
		}
		r->screeny += 1;
  	}
	pthread_mutex_unlock(&g_lock);
	pthread_exit(NULL);
	return (0);
}