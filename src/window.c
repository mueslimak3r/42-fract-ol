/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:56:37 by calamber          #+#    #+#             */
/*   Updated: 2019/07/15 21:14:05 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		cam_reset(t_mlx *mlx)
{
	mlx->cam->scale = 1;
	mlx->cam->x = 0;
	mlx->cam->y = 0;
}

void		cam_scale(t_mlx *mlx, int x, int y, int arg)
{
	double newscale;

	newscale = (arg == 3 || arg == 1) ? 1.3 : 0.6;
	mlx->cam->scale = mlx->cam->scale * newscale;
	if (arg == 3 || arg == 2)
	{
		mlx->cam->x += x - (WIN_WIDTH / 2);
		mlx->cam->y += y - (WIN_HEIGHT / 2);
	}
	else
	{
		mlx->cam->x += (arg == 3 || arg == 1)
			? (WIN_WIDTH / 8) : -(WIN_WIDTH / 8);
		mlx->cam->y += (arg == 3 || arg == 1)
			? (WIN_HEIGHT / 8) : -(WIN_WIDTH / 8);
	}
	mlx->cam->x *= newscale;
	mlx->cam->y *= newscale;
}

void		mlxdel(t_mlx *mlx)
{
	if (mlx->window != NULL)
		mlx_destroy_window(mlx->mlx, mlx->window);
	if (mlx->cam != NULL)
		ft_memdel((void **)&mlx->cam);
	if (mlx->mouse != NULL)
		ft_memdel((void **)&mlx->mouse);
	if (mlx->image != NULL)
		del_image(mlx, mlx->image);
	exit(0);
}

int			newwindow(t_mlx *s, char *title)
{
	ft_memset(s, 0, sizeof(t_mlx));
	if (!(s->mlx = mlx_init()) ||
		!(s->window = mlx_new_window(s->mlx, WIN_WIDTH, WIN_HEIGHT, title)))
	{
		free(title);
		if (s->window)
			mlx_destroy_window(s->mlx, s->window);
		return (1);
	}
	free(title);
	return (0);
}

int			init(char *title, t_mlx *mlx)
{
	if (newwindow(mlx, title) || (mlx->cam = ft_memalloc(sizeof(t_cam)))
		== NULL || (mlx->mouse = ft_memalloc(sizeof(t_mouse))) == NULL
		|| (mlx->image = new_image(mlx)) == NULL)
		mlxdel(mlx);
	mlx->palette = 0;
	mlx->p_size = 4;
	mlx->c_lock = false;
	mlx->m_lock = true;
	mlx->mouse->locked = false;
	mlx->cam->x = 0;
	mlx->cam->y = 0;
	mlx->cam->scale = 1;
	mlx->cam->offsetx = WIN_WIDTH / 2;
	mlx->cam->offsety = WIN_HEIGHT / 2;
	return (1);
}
