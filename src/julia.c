#include "fractol.h"

void            julia_print(t_mlx *mlx, int x, int y, int it)
{
    //if (it == mlx->iterations) {
    //    image_set_pixel(mlx->image, x, y, BLACK);
    //}
    //else {
    //    image_set_pixel(mlx->image, x, y, RED * sqrt(it / mlx->iterations)); // color(hu, 100, 100);
    //}
    fractal_check_print(mlx, x, y, it);
}

int		calc(t_fractal_args *r, double x, double y)
{
	int			i;
	long double	temp;

	x = ((4.0 * x / r->xsize - 2.0) / r->mlx->cam->scale) + (r->xoffset / r->xsize);
	y = ((4.0 * y / r->ysize - 2.0) / r->mlx->cam->scale) + (r->yoffset / r->ysize);
	i = 0;
	while (x * x + y * y < 4.0 && i < r->mlx->iterations)
	{
		temp = x * x - y * y - (double)0.70176;
		y = 2 * x * y - (double)0.3842;
		x = temp;
		i++;
	}
	return (i);
}

void            *julia(void *args)
{
	t_fractal_args *r = args;
    printf("hello!\n");
	//if (r->mlx)
	//	printf("%p %p\n", r->mlx, r->mlx->image);
	pthread_mutex_lock(&g_lock);
  	//double XSize= r->xsize;
  	//double YSize= r->ysize;
  	//double MinIm=-1.0;// * r->mlx->cam->scale;
  	//double MaxIm=1.0;// * r->mlx->cam->scale;
  	//double MinRe=-2.0;// * r->mlx->cam->scale;
  	//double MaxRe=1.0;// * r->mlx->cam->scale;
  	//double StepX=(MaxRe-MinRe)/XSize;
  	//double StepY=(MaxIm-MinIm)/YSize;
	int sy= r->screeny;
	for(double y=r->yoffset;y<r->yend;y++)
	{
      	//double Im= MinIm+StepY*y;
		int sx = r->screenx;
		for(double x=r->xoffset; x<r->xend; x++)
      	{
          	//double Re=MinRe+StepX*x;
          	int it= calc(args, x, y);
            if (it < r->mlx->iterations)
			    julia_print(r->mlx, sx, sy, it);
			sx++;
			//r->screenx++;
		}
		sy++;
		//r->screeny++;
  	}
	pthread_mutex_unlock(&g_lock);
	//free(args);
	pthread_exit(NULL);
	return (0);
}

