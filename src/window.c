#include "fractol.h"

/*
 * Deletes everything associated with the MLX objects
 */
void    mlxdel(t_mlx *mlx)
{
	// If the mlx window is not null, then destroy it with the given function
	if (mlx->window != NULL)
		mlx_destroy_window(mlx->mlx, mlx->window);
	// If the cam object is not empty, it deletes it's address and the contents
	if (mlx->cam != NULL)
		ft_memdel((void **)&mlx->cam);
	// If the mouse object is not empty, it deletes it's address and the contents
	if (mlx->mouse != NULL)
		ft_memdel((void **)&mlx->mouse);
	// If the image object is not empty, it deletes it's address and the contents
	if (mlx->image != NULL)
		del_image(mlx, mlx->image);
	// Deletes the contents and frees the address of mlx
}

/*
 * Initializes and adjusts initial state of object before render; calls different 
 * functions from MLX to make previous statement true.
 */

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

int     init(char *title, t_mlx *mlx)
{

	// Allocate enough memory to fit mlx object into your program
	// The mlx_init function will create this connection between software and 
	// display. No parameters are needed, ant  it  will  return  a void * 
	// identifier, used for further calls to the library routines.
	// mlx_new_window      : manage windows
	// mlx_new_image       : manipulate images
	// Allocate enough memory for mouse and camera
	if (newwindow(mlx, title) || (mlx->cam = ft_memalloc(sizeof(t_cam))) == NULL ||
			(mlx->mouse = ft_memalloc(sizeof(t_mouse))) == NULL ||
			(mlx->image = new_image(mlx)) == NULL) 
	{	// Pass MLX into it's delete function which deletes everything created
		// in memory
        mlxdel(mlx);
		return (0);
    }
	// Passes the map into map
	// Fill the attributes of the camera in memory
	// Sets parameter for camera angle for x-position (initial rotation)
	mlx->cam->x = 0.5;
	// Sets parameter for camera angle for y-position (initial rotation)
	mlx->cam->y = 0.5;
	// Dynamically adjusts INITIAL scale of image, based on initial size of map
	mlx->cam->scale = 1;
	// Offset Initial x state at window 
	mlx->cam->offsetx = WIN_WIDTH / 2;
	// Offsets initial y state at window
	mlx->cam->offsety = WIN_HEIGHT / 2;
	return (1);
}
