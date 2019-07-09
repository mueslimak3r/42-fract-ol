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

void                mandelbrot_check_print(t_mlx *mlx, int x, int y, int it)
{
    if (x >= 0 && y <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT)
		image_set_pixel(mlx->image, x, y, colors(it));
}

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
			mandelbrot_check_print(r->mlx, sx, sy, it);
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

void				mlx_draw(t_mlx *mlx)
{
    bool             valid;

    valid = false;
    clear_image(mlx->image);
    if (ft_strcmp(mlx->type, "sierpinski") == 0)
    {
        sierpinski_init(mlx);
        valid = true;
    }
    if (ft_strcmp(mlx->type, "mandelbrot") == 0)
    {
        mandelbrot_init(mlx);
        valid = true;
    }
    if (valid == true)
        mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
    else
        mlx_string_put(mlx->mlx, mlx->window, WIN_WIDTH / 2 - 10, 10, WHITE, "bad selection");
}