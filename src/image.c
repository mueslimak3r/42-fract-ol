#include "fractol.h"

void	image_set_pixel(t_image *image, int x, int y, int color)
{
	// Error checking
	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	*(int *)(image->ptr + ((x + y * WIN_WIDTH) * image->bpp)) = color;
}

/*
 * Clears content of the memory address without freeing the pointer
 */
void	clear_image(t_image *image)
{
	// Sets the memory area of size height * width pointed to by the pointer to zero.
	ft_bzero(image->ptr, WIN_WIDTH * WIN_HEIGHT * image->bpp);
}

/*
 * Deletes the image object associated with the mlx object and image.
 */
t_image		*del_image(t_mlx *mlx, t_image *img)
{
	// If image is not null
	if (img != NULL)
	{
		// if image pointed from image is not null
		if (img->image != NULL)
			mlx_destroy_image(mlx->mlx, img->image);
		// Delete the address of image
		ft_memdel((void **)&img);
	}
	return (NULL);
}

/*
 * Creates a new image in memory. Can be manipulated later
 */
t_image		*new_image(t_mlx *mlx)
{
	t_image		*img;

	// Allocates new area in memory for image
	if ((img = ft_memalloc(sizeof(t_image))) == NULL)
		return (NULL);
	// Creates a new image in memory. Can be manipulated later
	if ((img->image = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT)) == NULL)
		return (del_image(mlx, img));
	// Function grabs the pointer address of image so that you can manipulate 
	// it later
	img->ptr = mlx_get_data_addr(img->image, &img->bpp, &img->stride, 
			&img->endian);
	// Bits per pixel: img->bpp = img->bpp / 8;
	img->bpp /= 8;
	return (img);
}