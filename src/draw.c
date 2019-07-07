#include "fractol.h"

void                sierpinski_r(t_mlx *mlx, t_triangle tri, int i, bool first);
t_triangle          new_triangles(t_triangle *tri, int nb);

static int	ft_abs(int n)
{
	return ((n > 0) ? n : (n * -1));
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
        image_set_pixel(mlx->image, start.x, start.y, 14358738 - (it * 100));
		start.x += dx / (float)steps;
		start.y += dy / (float)steps;
		i++;
	}
}

void                check_print(t_mlx *mlx, t_vect_2 *a, t_vect_2 *b, int i)
{
    if (a->x >= 0 && a->x <= WIN_WIDTH && a->y >= 0 && a->y <= WIN_HEIGHT)
        dda(mlx, *a, *b, i);
    else if (b->x >= 0 && b->x <= WIN_WIDTH && b->y >= 0 && b->y <= WIN_HEIGHT)
        dda(mlx, *a, *b, i);
}

t_triangle          new_triangles(t_triangle *tri, int nb)
{
    t_triangle      t;
    if (nb == 0)
    {
        t.child[0] = (t_vect_2){ ((tri->child[0].x + tri->child[1].x) * 0.5f), ((tri->child[0].y + tri->child[1].y) * 0.5f) };
        t.child[1] = (t_vect_2){ ((tri->child[0].x + tri->parent[1].x) * 0.5f), ((tri->child[0].y + tri->parent[1].y) * 0.5f) };
        t.child[2] = (t_vect_2){ ((tri->parent[1].x + tri->child[1].x) * 0.5f), ((tri->parent[1].y + tri->child[1].y) * 0.5f) };
        t.parent[0] = tri->child[1];
        t.parent[1] = tri->child[0];
        t.parent[2] = tri->parent[1];
    }
    if (nb == 1)
    {
        t.child[0] = (t_vect_2){ ((tri->child[1].x + tri->child[2].x) * 0.5f), ((tri->child[1].y + tri->child[2].y) * 0.5f) };
        t.child[1] = (t_vect_2){ ((tri->child[1].x + tri->parent[2].x) * 0.5f), ((tri->child[1].y + tri->parent[2].y) * 0.5f) };
        t.child[2] = (t_vect_2){ ((tri->parent[2].x + tri->child[2].x) * 0.5f), ((tri->parent[2].y + tri->child[2].y) * 0.5f) };
        t.parent[0] = tri->child[2];
        t.parent[1] = tri->child[1];
        t.parent[2] = tri->parent[2];
    }
    if (nb == 2)
    {
        t.child[0] = (t_vect_2){ ((tri->child[2].x + tri->child[0].x) * 0.5f), ((tri->child[2].y + tri->child[0].y) * 0.5f) };
        t.child[1] = (t_vect_2){ ((tri->child[2].x + tri->parent[0].x) * 0.5f), ((tri->child[2].y + tri->parent[0].y) * 0.5f) };
        t.child[2] = (t_vect_2){ ((tri->parent[0].x + tri->child[0].x) * 0.5f), ((tri->parent[0].y + tri->child[0].y) * 0.5f) };
        t.parent[0] = tri->child[0];
        t.parent[1] = tri->child[2];
        t.parent[2] = tri->parent[0];
    }
    return (t);
}

void                *sierpinski_thread(void *args)
{
    
    t_thread_args *r = args;
    t_triangle      *t;

    t = malloc(sizeof(t_triangle) * 3);

    *t = new_triangles(r->in, 0);
    *(t + 1) = new_triangles(r->in, 1);
    *(t + 2) = new_triangles(r->in, 2);
    pthread_mutex_lock(&g_lock);

    sierpinski_r(r->mlx, *t, 1, false);
    sierpinski_r(r->mlx, *(t + 1), 1, false);
    sierpinski_r(r->mlx, *(t + 2), 1, false);
    free(t);
    pthread_mutex_unlock(&g_lock);
    pthread_exit(NULL);
    return 0;
}



void                sierpinski_r(t_mlx *mlx, t_triangle tri, int i, bool first)
{
    if (mlx->iterations > 12)
        mlx->iterations = 12;
    if (i > mlx->iterations || i > 12)
        return ;
    t_triangle      *t;
    

    t = malloc(sizeof(t_triangle) * 3);
    check_print(mlx, &tri.parent[0], &tri.parent[1], i);
    check_print(mlx, &tri.parent[1], &tri.parent[2], i);
    check_print(mlx, &tri.parent[2], &tri.parent[0], i);
    *t = new_triangles(&tri, 0);
    *(t + 1) = new_triangles(&tri, 1);
    *(t + 2) = new_triangles(&tri, 2);
    if (first)
    {
        pthread_t       thread[3];
        if (pthread_mutex_init(&g_lock, NULL) != 0)
            printf("Mutex initialization failed.\n");
        for (int i = 0; i < 3; i++)
        {
            t_thread_args args = ((t_thread_args){ i, mlx, t + i });
            pthread_create(&thread[i], NULL, sierpinski_thread, &args);
            pthread_join(thread[i], NULL);
        }
    }
    else
    {
        sierpinski_r(mlx, *t, i + 1, false);
        sierpinski_r(mlx, *(t + 1), i + 1, false);
        sierpinski_r(mlx, *(t + 2), i + 1, false);
    }
    free(t);
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
    tri.parent[2].y = cam->offsety + (alt / 2);
    tri.child[0] = (t_vect_2){ ((tri.parent[0].x + tri.parent[1].x) * 0.5f), ((tri.parent[0].y + tri.parent[1].y) * 0.5f) };
    tri.child[1] = (t_vect_2){ ((tri.parent[1].x + tri.parent[2].x) * 0.5f), ((tri.parent[1].y + tri.parent[2].y) * 0.5f) };
    tri.child[2] = (t_vect_2){ ((tri.parent[2].x + tri.parent[0].x) * 0.5f), ((tri.parent[2].y + tri.parent[0].y) * 0.5f) };
    sierpinski_r(mlx, tri, 0, true);
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