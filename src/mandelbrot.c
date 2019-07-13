/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 22:47:21 by calamber          #+#    #+#             */
/*   Updated: 2019/07/12 23:25:17 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int				m_calc(t_mlx *mlx, double re, double im)
{
	double	zr;
	double	zi;
	double	a;
	double	b;
	int		it;

	zr = re;
	zi = im;
	it = 0;
	while (it < mlx->iterations)
	{
		a = zr * zr;
		b = zi * zi;
		if (a + b > 4.0)
			break ;
		zi = 2 * zr * zi + im;
		zr = a - b + re;
		it++;
	}
	return (it);
}

void			*mandelbrot(void *args)
{
	t_fractal_args	*r;
	int				it;
	int				sx;
	double			x;

	r = args;
	pthread_mutex_lock(&g_lock);
	while (r->yoffset++ < r->yend)
	{
		sx = r->screenx;
		x = r->xoffset;
		while (x++ < r->xend)
		{
			it = m_calc(r->mlx, (-2.0 + ((1.0 - (-2.0)) / r->xsize) * x),
				(-1.0 + ((1.0 - (-1.0)) / r->ysize) * r->yoffset));
			fractal_check_print(r->mlx, sx, r->screeny, it);
			sx++;
		}
		r->screeny += 1;
	}
	free(args);
	pthread_mutex_unlock(&g_lock);
	pthread_exit(NULL);
	return (0);
}
