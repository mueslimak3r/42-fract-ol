#include "fractol.h"

int		die(char *reason)
{
	ft_putendl(reason);
	return (1);
}

int main (int ac, char **av)
{
    t_mlx mlx;
    if (ac < 2)
        return(die("usage:"));
    if (!(init(ft_strjoin("fractol - ", av[1]), &mlx)))
        return(die("error"));
    start(&mlx);
    return (0);
}