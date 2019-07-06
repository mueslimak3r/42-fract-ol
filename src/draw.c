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
	while (i <= steps)
	{
        if (i == (steps / 2) - 1)
            end = (t_vect_2){ start.x, start.y };
        if (start.x >= 0 && start.x <= WIN_WIDTH && start.y >= 0 && start.y <= WIN_HEIGHT)
            image_set_pixel(mlx->image, start.x, start.y, 14358738);
		start.x += dx / (float)steps;
		start.y += dy / (float)steps;
		i++;
	}
    return (end);
}
/*
static              thread_solve()
{

}
*/
void                sierpinski_r(t_mlx *mlx, t_triangle tri, int i)
{
    if (i > mlx->iterations)
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
    sierpinski_r(mlx, t1, i + 1);
    sierpinski_r(mlx, t2, i + 1);
    sierpinski_r(mlx, t3, i + 1);
}

void                sierpinski_init(t_mlx *mlx)
{
    t_triangle      tri;
    t_cam           *cam = mlx->cam;
    double          side = (WIN_WIDTH / 2) * cam->scale;
    double          alt = (sqrt(3) / 2) * side;
    tri.parent[0].x = cam->offsetx - (side / 2);
    tri.parent[0].y = cam->offsety - (alt / 2);
    tri.parent[1].x = cam->offsetx + (side / 2);
    tri.parent[1].y = cam->offsety - (alt / 2);
    tri.parent[2].x = cam->offsetx;
    tri.parent[2].y = cam->offsety + (alt / 2);;
    tri.child[0] = dda(mlx, tri.parent[0], tri.parent[1]);
    tri.child[1] = dda(mlx, tri.parent[1], tri.parent[2]);
    tri.child[2] = dda(mlx, tri.parent[2], tri.parent[0]);
    sierpinski_r(mlx, tri, 0);
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
    if (valid == true)
        mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
    else
        mlx_string_put(mlx->mlx, mlx->window, WIN_WIDTH / 2 - 10, 10, WHITE, "bad selection");
}