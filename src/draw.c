#include "fractol.h"

static int	ft_abs(int n)
{
	return ((n > 0) ? n : (n * -1));
}

t_vect_2        dda(t_mlx *mlx, t_vect_2 start, t_vect_2 end)
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
        if (i == (steps / 2) - 1)
            end = (t_vect_2){ start.x, start.y };
        image_set_pixel(mlx->image, start.x, start.y, 14358738);
		start.x += dx / (float)steps;
		start.y += dy / (float)steps;
		i++;
	}
    return (end);
    //printf("\n");
}
/*
void                flip(t_mlx *mlx, t_vect_2 mid_1, t_vect_2 mid_2, t_vect_2 mid_3, int i)
{
    t_vect_2 r_1;
    t_vect_2 r_2;
    t_vect_2 r_3;

    theta = degreesToRadians(180);

cs = cos(theta);
sn = sin(theta);

x = x * cs - y * sn;
y = x * sn + y * cs;

    sierpinksi_r(mlx, mid_1, mid_2, mid_3, i + 1);
}
*/

void                sierpinksi_r(t_mlx *mlx, t_vect_2 m_1, t_vect_2 m_2, t_vect_2 m_3, int i)
{
    if (i > 10)
        return ;
    t_vect_2        mid_1 = dda(mlx, m_1, m_2);
    t_vect_2        mid_2 = dda(mlx, m_3, m_1);
    t_vect_2        mid_3 = dda(mlx, m_2, m_3);
    //flip(mlx, mid_1, mid_2, mid_3, i);
    sierpinksi_r(mlx, mid_1, mid_2, mid_3, i + 1);
}

void                sierpinksi_init(t_mlx *mlx)
{
    t_vect_2        one;
    t_vect_2        two;
    t_vect_2        three;

    t_vect_2        m_1;
    t_vect_2        m_2;
    t_vect_2        m_3;

    double          side = WIN_WIDTH / 2;
    double          alt = (sqrt(3) / 2) * side;
    one.x = (WIN_WIDTH - (side)) / 2;
    one.y = (WIN_HEIGHT - alt) / 2;
    two.x = WIN_WIDTH - (WIN_WIDTH - (side)) / 2;
    two.y = (WIN_HEIGHT - alt) / 2;
    three.x = WIN_WIDTH / 2;
    three.y = ((WIN_HEIGHT - alt) / 2) + alt;
    m_1 = dda(mlx, one, two);
    m_2 = dda(mlx, three, one);
    m_3 = dda(mlx, two, three);
    sierpinksi_r(mlx, m_1, m_2, m_3, 0);
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