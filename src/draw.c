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

void                sierpinksi_r(t_mlx *mlx, t_triangle tri, int i)
{
    if (i > 10)
        return ;
    t_triangle      t1;
    t_triangle      t2;
    t_triangle      t3;

    
    t1.child[0] = dda(mlx, tri.child[0], tri.child[1]);
    t2.child[0] = dda(mlx, tri.child[1], tri.child[2]);
    t3.child[0] = dda(mlx, tri.child[2], tri.child[0]);

    t1.child[1] = dda(mlx, tri.child[0], tri.parent[1]);
    t1.child[2] = dda(mlx, tri.parent[1], tri.child[1]);
    
    t2.child[1] = dda(mlx, tri.child[1], tri.parent[2]);
    t2.child[2] = dda(mlx, tri.parent[2], tri.child[2]);
    
    t3.child[1] = dda(mlx, tri.child[2], tri.parent[0]);
    t3.child[2] = dda(mlx, tri.parent[0], tri.child[0]);

    t1.parent[0] = tri.child[1];
    t1.parent[1] = tri.child[0];
    t1.parent[2] = tri.parent[1];
    t2.parent[0] = tri.child[2];
    t2.parent[1] = tri.child[1];
    t2.parent[2] = tri.parent[2];
    t3.parent[0] = tri.child[0];
    t3.parent[1] = tri.child[2];
    t3.parent[2] = tri.parent[0];
    
    sierpinksi_r(mlx, t1, i + 1);
    sierpinksi_r(mlx, t2, i + 1);
    sierpinksi_r(mlx, t3, i + 1);
}

void                sierpinksi_init(t_mlx *mlx)
{
    t_triangle      tri;

    double          side = WIN_WIDTH / 2;
    double          alt = (sqrt(3) / 2) * side;
    tri.parent[0].x = (WIN_WIDTH - (side)) / 2;
    tri.parent[0].y = (WIN_HEIGHT - alt) / 2;
    tri.parent[1].x = WIN_WIDTH - (WIN_WIDTH - (side)) / 2;
    tri.parent[1].y = (WIN_HEIGHT - alt) / 2;
    tri.parent[2].x = WIN_WIDTH / 2;
    tri.parent[2].y = ((WIN_HEIGHT - alt) / 2) + alt;
    tri.child[0] = dda(mlx, tri.parent[0], tri.parent[1]);
    tri.child[1] = dda(mlx, tri.parent[1], tri.parent[2]);
    tri.child[2] = dda(mlx, tri.parent[2], tri.parent[0]);
    sierpinksi_r(mlx, tri, 0);
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