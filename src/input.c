/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:48:36 by calamber          #+#    #+#             */
/*   Updated: 2019/07/14 00:03:37 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		cam_scale(t_mlx *mlx, int x, int y, bool mouse, bool in)
{
	double		oldx; 
	double		oldy;
	//int		offsetx;
	//int		offsety;

	if (x || y)
		;
	oldx = mlx->cam->x;
	oldy = mlx->cam->y;
	double newscale = mlx ->cam->scale * (in ? 1.3 : 0.6);
	if (!mouse)
	{
		//oldx += (WIN_WIDTH * mlx->cam->scale) / 4;
		//oldy += (WIN_HEIGHT * mlx->cam->scale) / 4;
	//	offsetx = -(oldx * mlx->cam->scale);
	//	offsety = -(oldx * mlx->cam->scale);
		//mlx->cam->x -= WIN_WIDTH / 2;
		//mlx->cam->y -= WIN_HEIGHT / 2;
		//mlx->cam->x += (oldx * newscale);
		//mlx->cam->y += (oldy * newscale);
		//oldx += (WIN_WIDTH * mlx->cam->scale) / 4;
		//oldy += (WIN_HEIGHT * mlx->cam->scale) / 4;
		////mlx->cam->x = oldx;
		mlx->cam->scale = newscale;	
	}
	//mlx->cam->x = in ? oldx - offsetx : oldx + offsetx;
	//mlx->cam->y = in ? oldx - offsety : oldx + offsety;
}

int			hook_mouse_press(int button, int x, int y, t_mlx *mlx)
{
	(void)x;
	if (y < 0)
		return (0);
	if (button == 1)
	{
		mlx->mouse->clicked = true;
		return (0);
	}
	if (button == 4)
		mlx->cam->scale *= 1.3;
	else if (button == 5)
	{
		if (mlx->cam->scale * 0.6 <= 0)
			return (0);
		mlx->cam->scale *= 0.6;
	}
	mlx_draw(mlx);
	return (0);
}

int			hook_mousemove(int x, int y, t_mlx *mlx)
{
	mlx->mouse->lastx = mlx->mouse->x;
	mlx->mouse->lasty = mlx->mouse->y;
	mlx->mouse->x = x;
	mlx->mouse->y = y;
	if (!mlx->m_lock)
	{
		mlx->c_lock = true;
		mlx->palette += (x > mlx->mouse->lastx ||
			y > mlx->mouse->lasty) ? 1 : -1;
	}
	if (mlx->palette < 0 || mlx->palette > 3)
		mlx->palette = (mlx->palette < 0) ? 3 : 0;
	if (mlx->mouse->clicked)
		mlx->cam->scale *= 1.3;
	mlx_draw(mlx);
	return (0);
}

static int	fdf_key_hook(int key, t_mlx *mlx)
{
	if (key == KEY_ESCAPE)
		mlxdel(mlx);
	if (key == KEY_W || key == KEY_PAD_1)
		cam_scale(mlx, 0, 0, false, true);
	if (key == KEY_S || key == KEY_PAD_2)
		cam_scale(mlx, 0, 0, false, false);
	if (key == KEY_I || key == KEY_PAD_4)
		mlx->iterations += ft_strcmp(mlx->type, "sierpinski") == 0 ? 1 : 25;
	if (key == KEY_R || key == KEY_PAD_5)
		mlx->iterations -= mlx->iterations - 1 < 0 ? 0 : 1;
	if (key == KEY_BACKSPACE)
		cam_reset(mlx);
	if (key == KEY_L)
		mlx->c_lock = mlx->c_lock ? false : true;
	if (key == KEY_M)
		mlx->m_lock = mlx->m_lock ? false : true;
	if (key == KEY_P && (mlx->c_lock = true))
		mlx->palette = (mlx->palette == 3) ? 0 : mlx->palette + 1;
	if (key == KEY_UP || key == KEY_DOWN)
		mlx->cam->y += key == KEY_UP ? -50 : 50;
	if (key == KEY_LEFT || key == KEY_RIGHT)
		mlx->cam->x += key == KEY_RIGHT ? 50 : -50;
	mlx_draw(mlx);
	return (0);
}

void		start(t_mlx *mlx)
{
	if (ft_strcmp(mlx->type, "sierpinski") == 0)
		mlx->iterations = 10;
	if (ft_strcmp(mlx->type, "mandelbrot") == 0)
		mlx->iterations = 50;
	if (ft_strcmp(mlx->type, "julia") == 0)
		mlx->iterations = 50;
	mlx_draw(mlx);
	mlx_hook(mlx->window, 4, 0, hook_mouse_press, mlx);
	mlx_hook(mlx->window, 6, 0, hook_mousemove, mlx);
	mlx_hook(mlx->window, 2, 5, fdf_key_hook, mlx);
	mlx_loop(mlx->mlx);
}
