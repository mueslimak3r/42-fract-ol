/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:37:16 by calamber          #+#    #+#             */
/*   Updated: 2019/07/12 23:46:00 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		calc(t_fractal_args *r, double x, double y)
{
	int			i;
	long double	temp;

	x = ((4.0 * x / r->xsize - 2.0) / r->mlx->cam->scale);
	y = ((4.0 * y / r->ysize - 2.0) / r->mlx->cam->scale);
	i = 0;
	while (x * x + y * y < 4.0 && i < r->mlx->iterations)
	{
		temp = x * x - y * y + (r->mlx->mouse->x * 4.0 / r->xsize - 2);
		y = 2 * x * y + (r->mlx->mouse->y * 4.0 / r->ysize - 2);
		x = temp;
		i++;
	}
	return (i);
}

void			*julia(void *args)
{
	t_fractal_args	*r;
	int				sx;
	double			x;
	int				it;

	r = args;
	pthread_mutex_lock(&g_lock);
	while (r->yoffset++ < r->yend)
	{
		sx = r->screenx;
		x = r->xoffset;
		while (x++ < r->xend)
		{
			it = calc(args, x, r->yoffset);
			if (it < r->mlx->iterations)
				fractal_check_print(r->mlx, sx, r->screeny, it);
			sx++;
		}
		r->screeny++;
	}
	free(args);
	pthread_mutex_unlock(&g_lock);
	pthread_exit(NULL);
	return (0);
}
