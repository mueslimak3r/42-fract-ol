#include "fractol.h"

void            *mandelbrot(void *args)
{
	t_fractal_args *r = args;

	//if (r->mlx)
	//	printf("%p %p\n", r->mlx, r->mlx->image);
	pthread_mutex_lock(&g_lock);
  	double XSize= r->xsize;
  	double YSize= r->ysize;
  	double MinIm=-1.0;// * r->mlx->cam->scale;
  	double MaxIm=1.0;// * r->mlx->cam->scale;
  	double MinRe=-2.0;// * r->mlx->cam->scale;
  	double MaxRe=1.0;// * r->mlx->cam->scale;
  	double StepX=(MaxRe-MinRe)/XSize;
  	double StepY=(MaxIm-MinIm)/YSize;
	int sy= r->screeny;
	for(double y=r->yoffset;y<r->yend;y++)
	{
      	double Im=MinIm+StepY*y;
		int sx = r->screenx;
		for(double x=r->xoffset; x<r->xend; x++)
      	{
          	double Re=MinRe+StepX*x;
          	double Zr=Re;
          	double Zi=Im;
          	int it=0;
        	for(int n=0;n<r->mlx->iterations;n++)
		  	{
				it = n;
				double a=Zr*Zr;
				double b=Zi*Zi;
            	if(a+b>4.0)
			  		break;
            	Zi=2*Zr*Zi+Im;
				Zr=a-b+Re;
			}
			fractal_check_print(r->mlx, sx, sy, it);
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
/*
void				mandelbrot_init(t_mlx *mlx)
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
		pthread_create(&thread[i], NULL, mandelbrot, &args);
		pthread_join(thread[i], NULL);
	}
}
*/