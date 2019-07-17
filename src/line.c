/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:53:45 by calamber          #+#    #+#             */
/*   Updated: 2019/07/15 17:37:07 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	ft_abs(int n)
{
	return ((n > 0) ? n : (n * -1));
}

void		dda(t_mlx *mlx, t_vect_2 start, t_vect_2 end, int it)
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
		image_set_pixel(mlx->image, start.x, start.y, colors(it, mlx));
		start.x += dx / (float)steps;
		start.y += dy / (float)steps;
		i++;
	}
}

void		sierpinski_helper(t_triangle t[3], t_mlx *mlx, int i, bool first)
{
	pthread_t		thread[3];
	t_serp_args		args;
	int				th;

	th = 0;
	if (first && mlx->iterations > 1)
	{
		if (pthread_mutex_init(&g_lock, NULL) != 0)
			ft_printf("Mutex initialization failed.\n");
		while (th < 3)
		{
			args = ((t_serp_args){ i, mlx, &t[th] });
			pthread_create(&thread[th], NULL, sierpinski_thread, &args);
			pthread_join(thread[th], NULL);
			th++;
		}
	}
	else
	{
		sierpinski_r(mlx, t[0], i + 1, false);
		sierpinski_r(mlx, t[1], i + 1, false);
		sierpinski_r(mlx, t[2], i + 1, false);
	}
}

void		new_tri_helper(t_triangle *t, t_triangle *tri, int nb)
{
	if (nb == 1)
	{
		t->child[1] = (t_vect_2){ ((tri->child[1].x + tri->parent[2].x) * 0.5f),
			((tri->child[1].y + tri->parent[2].y) * 0.5f) };
		t->child[2] = (t_vect_2){ ((tri->parent[2].x + tri->child[2].x) * 0.5f),
			((tri->parent[2].y + tri->child[2].y) * 0.5f) };
		t->parent[0] = tri->child[2];
		t->parent[1] = tri->child[1];
		t->parent[2] = tri->parent[2];
	}
	if (nb == 2)
	{
		t->child[0] = (t_vect_2){ ((tri->child[2].x + tri->child[0].x) * 0.5f),
			((tri->child[2].y + tri->child[0].y) * 0.5f) };
		t->child[1] = (t_vect_2){ ((tri->child[2].x + tri->parent[0].x) * 0.5f),
			((tri->child[2].y + tri->parent[0].y) * 0.5f) };
		t->child[2] = (t_vect_2){ ((tri->parent[0].x + tri->child[0].x) * 0.5f),
			((tri->parent[0].y + tri->child[0].y) * 0.5f) };
		t->parent[0] = tri->child[0];
		t->parent[1] = tri->child[2];
		t->parent[2] = tri->parent[0];
	}
}
