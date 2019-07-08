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
	t_thread_args *r = args;

	//if (r->mlx)
	//	printf("%p %p\n", r->mlx, r->mlx->image);
	pthread_mutex_lock(&g_lock);
  	int XSize= r->xsize == 0 ? (1920 / 2) : r->xsize * 2;
  	int YSize= r->ysize == 0 ? (1080 / 2) : r->ysize * 2;
  	double MinIm=-1.0;
  	double MaxIm=1.0;
  	double MinRe=-2.0;
  	double MaxRe=1.0;
  	double StepX=(MaxRe-MinRe)/XSize;
  	double StepY=(MaxIm-MinIm)/YSize;
  	for(int y=r->ysize;y<YSize;y++)
	{
      	double Im=MinIm+StepY*y;
      	for(int x=r->xsize; x<XSize; x++)
      	{
          	double Re=MinRe+StepX*x;
          	double Zr=Re;
          	double Zi=Im;
          	int it=0;
        	for(int n=0;n<120;n++)
		  	{
				it = n;
				double a=Zr*Zr;
				double b=Zi*Zi;
            	if(a+b>4.0) 
			  		break;
            	Zi=2*Zr*Zi+Im;
				Zr=a-b+Re;
			}
			mandelbrot_check_print(r->mlx, x, y, it);
    	}
  	}
	pthread_mutex_unlock(&g_lock);
	pthread_exit(NULL);
	return (0);
}

void				mandelbrot_init(t_mlx *mlx)
{
	pthread_t       thread[4];
	if (pthread_mutex_init(&g_lock, NULL) != 0)
            printf("Mutex initialization failed.\n");
    for (int i = 0; i < 4; i++)
    {
		t_thread_args args;
		if (i == 0)
			args = ((t_thread_args){ 0, 0, 0, mlx, NULL });
		if (i == 1)
			args = ((t_thread_args){ WIN_WIDTH / 2, 0, 0, mlx, NULL });
		if (i == 2)
			args = ((t_thread_args){ WIN_WIDTH / 2, WIN_HEIGHT / 2, 0, mlx, NULL });
		if (i == 3)
			args = ((t_thread_args){ 0, WIN_HEIGHT / 2, 0, mlx, NULL });
		pthread_create(&thread[i], NULL, mandelbrot, &args);
		pthread_join(thread[i], NULL);
		
	}
	//for (int i = 0; i < 1; i++)
		
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