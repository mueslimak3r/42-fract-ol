/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:53:45 by calamber          #+#    #+#             */
/*   Updated: 2019/07/12 23:54:03 by calamber         ###   ########.fr       */
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
		image_set_pixel(mlx->image, start.x, start.y, colors(it));
		start.x += dx / (float)steps;
		start.y += dy / (float)steps;
		i++;
	}
}
