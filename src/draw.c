/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:12:45 by calamber          #+#    #+#             */
/*   Updated: 2019/07/13 20:11:22 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int						colors(int i, t_mlx *mlx)
{
	int *rgb[mlx->p_size];

	rgb[0] = (int[3]){ RED, GREEN, BLUE };
	rgb[1] = (int[3]){ FLAMINGO, YELLOW, AQUA_MARINE };
	rgb[2] = (int[3]){ DARK_GRAY, HONEYDEW, SALMON };
	rgb[3] = (int[3]){ LAVENDER, MIDNIGHT_BLUE, PURPLE };
	if (mlx->c_lock)
		return (rgb[mlx->palette][i % 3]);
	return (rgb[i % mlx->p_size][i % 3]);
}

void					fractal_check_print(t_mlx *mlx, int x, int y, int it)
{
	if (x >= 0 && y <= WIN_WIDTH && y >= 0 && y <= WIN_HEIGHT)
		image_set_pixel(mlx->image, x, y, colors(it, mlx));
}

static t_fractal_args	*f_args_make(t_mlx *mlx, int nb)
{
	t_fractal_args	*new;
	t_cam			*cam;
	double			xsize;
	double			ysize;

	new = ft_memalloc(sizeof(t_fractal_args));
	xsize = WIN_WIDTH * mlx->cam->scale;
	ysize = WIN_HEIGHT * mlx->cam->scale;
	cam = mlx->cam;
	if (nb == 0)
		*new = ((t_fractal_args){ xsize, ysize, 0, 0, cam->x, cam->y,
		cam->x + (WIN_WIDTH / 2), cam->y + (WIN_HEIGHT / 2), mlx });
	if (nb == 1)
		*new = ((t_fractal_args){ xsize, ysize, WIN_WIDTH / 2, 0,
		cam->x + (WIN_WIDTH / 2), cam->y, cam->x + WIN_WIDTH, cam->y
		+ (WIN_HEIGHT / 2), mlx });
	if (nb == 2)
		*new = ((t_fractal_args){ xsize, ysize, WIN_WIDTH / 2,
		WIN_HEIGHT / 2, cam->x + (WIN_WIDTH / 2), cam->y + (WIN_HEIGHT / 2),
		cam->x + WIN_WIDTH, cam->y + WIN_HEIGHT, mlx });
	if (nb == 3)
		*new = ((t_fractal_args){ xsize, ysize, 0, WIN_HEIGHT / 2,
		cam->x, cam->y + (WIN_HEIGHT / 2), cam->x + (WIN_WIDTH / 2),
		cam->y + WIN_HEIGHT, mlx });
	return (new);
}

void					fractal_init(t_mlx *mlx, void *(*fractal)(void *))
{
	pthread_t		thread[4];
	int				i;

	if (pthread_mutex_init(&g_lock, NULL) != 0)
		ft_printf("Mutex initialization failed.\n");
	i = 0;
	while (i < 4)
	{
		pthread_create(&thread[i], NULL, fractal, f_args_make(mlx, i));
		pthread_join(thread[i], NULL);
		i++;
	}
}

void					mlx_draw(t_mlx *mlx)
{
	bool	valid;

	valid = true;
	mlx->mouse->clicked = false;
	clear_image(mlx->image);
	mlx_clear_window(mlx->mlx, mlx->window);
	if (ft_strcmp(mlx->type, "sierpinski") == 0)
		sierpinski_init(mlx);
	else if (ft_strcmp(mlx->type, "mandelbrot") == 0)
		fractal_init(mlx, mandelbrot);
	else if (ft_strcmp(mlx->type, "julia") == 0)
		fractal_init(mlx, julia);
	else
		valid = false;
	mlx_string_put(mlx->mlx, mlx->window, 10, WIN_HEIGHT - 30,
		WHITE, "ESC: close");
	if (valid == true)
		mlx_put_image_to_window(mlx->mlx, mlx->window, mlx->image->image, 0, 0);
	else
		mlx_string_put(mlx->mlx, mlx->window, WIN_WIDTH / 2 - 10, 10,
			WHITE, "bad selection");
}
