#include "fractol.h"

void                sierpinski_r(t_mlx *mlx, t_triangle tri, int i, bool first);
t_triangle          new_triangles(t_triangle *tri, int nb);

void                s_check_print(t_mlx *mlx, t_vect_2 *a, t_vect_2 *b, int i)
{
    t_vect_2        mid;

    mid = (t_vect_2){ ((a->x + b->x) * 0.5f), ((a->y + b->y) * 0.5f) };
    if (a->x >= 0 && a->x <= WIN_WIDTH && a->y >= 0 && a->y <= WIN_HEIGHT)
        dda(mlx, *a, *b, i);
    else if (b->x >= 0 && b->x <= WIN_WIDTH && b->y >= 0 && b->y <= WIN_HEIGHT)
        dda(mlx, *a, *b, i);
   else if (mid.x >= 0 && mid.x <= WIN_WIDTH && mid.y >= 0 && mid.y <= WIN_HEIGHT)
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
    s_check_print(r->mlx, &t->parent[0], &t->parent[1], 2);
    s_check_print(r->mlx, &(t + 1)->parent[0], &(t + 1)->parent[1], 2);
    s_check_print(r->mlx, &(t + 2)->parent[0], &(t + 2)->parent[1], 2);
    sierpinski_r(r->mlx, *t, 3, false);
    sierpinski_r(r->mlx, *(t + 1), 3, false);
    sierpinski_r(r->mlx, *(t + 2), 3, false);
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
    s_check_print(mlx, &tri.child[0], &tri.child[1], i);
    s_check_print(mlx, &tri.child[1], &tri.child[2], i);
    s_check_print(mlx, &tri.child[2], &tri.child[0], i);
    *t = new_triangles(&tri, 0);
    *(t + 1) = new_triangles(&tri, 1);
    *(t + 2) = new_triangles(&tri, 2);
    if (first && mlx->iterations > 1)
    {
        pthread_t       thread[3];
        if (pthread_mutex_init(&g_lock, NULL) != 0)
            printf("Mutex initialization failed.\n");
        for (int i = 0; i < 3; i++)
        {
            t_thread_args args = ((t_thread_args){ 0, 0, i, mlx, t + i });
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
    s_check_print(mlx, &tri.parent[0], &tri.parent[1], 0);
    s_check_print(mlx, &tri.parent[1], &tri.parent[2], 0);
    s_check_print(mlx, &tri.parent[2], &tri.parent[0], 0);
    sierpinski_r(mlx, tri, 1, true);
}