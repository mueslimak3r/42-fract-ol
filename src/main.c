/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 23:55:07 by calamber          #+#    #+#             */
/*   Updated: 2019/07/15 21:17:16 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			die(char *reason)
{
	ft_putendl(reason);
	return (1);
}

static void	print_info(void)
{
	ft_putendl("welcome!");
	ft_putendl("\ncontrols:");
	ft_putendl("move: click region to zoom and move or use arrow keys");
	ft_putendl("zoom: left mouse click or w && s or npad 1 && 2");
	ft_putendl("change iterations: i && r or npad 4 && 5");
	ft_putstr("toggles:\n manual color mode: L to enable,");
	ft_putendl(" P to cycle through palettes\npsychedelic mode: M");
	ft_putendl("\nlock camera: K");
	ft_putendl("\nrun: ./fractol type");
	ft_putendl("\ntypes:");
	ft_putendl("mandelbrot");
	ft_putendl("julia");
	ft_putendl("sierpinski");
}

int			main(int ac, char **av)
{
	t_mlx *mlx;

	mlx = malloc(sizeof(t_mlx));
	if (ac < 2)
	{
		print_info();
		return (die("\nerror: bad arguments"));
	}
	if (!(init(ft_strjoin("fractol - ", av[1]), mlx)))
		return (die("error"));
	mlx->type = av[1];
	print_info();
	start(mlx);
	return (0);
}
