#include "fractol.h"

static int	ft_abs(int n)
{
	return ((n > 0) ? n : (n * -1));
}

void		dda(t_mlx *mlx, t_vect_2 start, t_vect_2 end)
{
	int	dx;
	int	dy;
	int	steps;
	int	i;

	dx = (int)end.x - (int)start.x;
	dy = (int)end.y - (int)start.y;
	steps = ft_abs(dx) > ft_abs(dy) ? ft_abs(dx) : ft_abs(dy);
	i = 0;
    //printf("start: %d %d\n", start.x, start.y);
	while (i <= steps)
	{
        //printf("%d %d\n", start.x, start.y);
        image_set_pixel(mlx->image, start.x, start.y, 14358738);
		start.x += dx / (float)steps;
		start.y += dy / (float)steps;
		i++;
	}
    //printf("\n");
}
/*
void                sierpinksi_r(t_mlx *mlx, t_vect_2 one, t_vect_2 two, int i)
{
    if (i > 10)
        return ;
    t_vect_2        three;

}
*/
void                sierpinksi_init(t_mlx *mlx)
{
    t_vect_2        one;
    t_vect_2        two;
    t_vect_2        three;
    double          side = WIN_WIDTH / 2;
    double          alt = (sqrt(3) / 2) * side;
    one.x = (WIN_WIDTH - (side)) / 2;
    one.y = (WIN_HEIGHT - alt) / 2;
    two.x = WIN_WIDTH - (WIN_WIDTH - (side)) / 2;
    two.y = (WIN_HEIGHT - alt) / 2;
    three.x = WIN_WIDTH / 2;
    three.y = ((WIN_HEIGHT - alt) / 2) + alt;
    printf("1: %f %f\n", one.x, one.y);
    printf("2: %f %f\n", two.x, two.y);
    printf("3: %f %f\n", three.x, three.y);
    image_set_pixel(mlx->image, one.x, one.y, 14358738);
    image_set_pixel(mlx->image, two.x, two.y, 14358738);
    image_set_pixel(mlx->image, three.x, three.y, 14358738);
    dda(mlx, one, two);
    dda(mlx, three, one);
    dda(mlx, two, three);
}

void				mlx_draw(t_mlx *mlx)
{
    clear_image(mlx->image);
    /*for (int y = 0; y < WIN_HEIGHT; y++)
        for (int x = 0; x < WIN_WIDTH; x++)
            image_set_pixel(mlx->image, x, y, 14358738);
    */
    sierpinksi_init(mlx);
    mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
}