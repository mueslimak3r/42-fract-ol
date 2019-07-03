#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "colors.h"
# include "keycode_mac.h"
# include "mlx.h"
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define MENU_WIDTH 100
# define FT_MIN(A, B) (((A) < (B)) ? (A) : (B))
#define degreesToRadians(angleDegrees) ((angleDegrees) * M_PI / 180.0)

typedef struct		s_map
{
	int				width;
	int				height;
	int				depth_min;
	int				depth_max;
	int				*colors;
	int				color1;
	int				color2;
	int				iter;
}					t_map;

typedef struct		s_vect_2
{
	double				x;
	double				y;
}					t_vect_2;

typedef struct		s_image
{
	void			*image;
	char			*ptr;
	int				bpp;
	int				stride;
	int				endian;
}					t_image;

typedef struct		s_cam
{
	double			offsetx;
	double			offsety;
	double			x;
	double			y;
	int				scale;
	double			**matrix;
}					t_cam;

typedef struct		s_mouse
{
	char			is_down;
	int				x;
	int				y;
	int				lastx;
	int				lasty;
}					t_mouse;

typedef struct		s_mlx
{
	void			*mlx;
	void			*window;
	t_image			*image;
	t_cam			*cam;
	t_mouse			*mouse;
	// double			**zbuf;
}					t_mlx;

int					init(char *title, t_mlx *mlx);
void				mlx_draw(t_mlx *mlx);
void				mlxdel(t_mlx *mlx);
t_image				*new_image(t_mlx *mlx);
t_image				*del_image(t_mlx *mlx, t_image *img);
void				clear_image(t_image *image);
void				start(t_mlx *mlx);
void				image_set_pixel(t_image *image, int x, int y, int color);
#endif