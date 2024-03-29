/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: calamber <calamber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 17:44:17 by calamber          #+#    #+#             */
/*   Updated: 2019/07/15 21:14:12 by calamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/libft.h"
# include "colors.h"
# ifdef __linux__
# include "keycode_linux.h"
# else
# include "keycode_mac.h"
# endif
# include "mlx.h"
# include <math.h>
# include <limits.h>
# include <fcntl.h>
# include <stdlib.h>
# include <pthread.h>

# define WIN_WIDTH 640
# define WIN_HEIGHT 480
# define MENU_WIDTH 100
# define FT_MIN(A, B) (((A) < (B)) ? (A) : (B))

typedef struct s_triangle	t_triangle;
typedef struct s_map		t_map;
pthread_mutex_t				g_lock;

struct						s_map
{
	int	width;
	int	height;
	int	depth_min;
	int	depth_max;
	int	*colors;
	int	color1;
	int	color2;
	int	iter;
};

typedef struct				s_vect_2
{
	double					x;
	double					y;
}							t_vect_2;

typedef struct				s_image
{
	void					*image;
	char					*ptr;
	int						bpp;
	int						stride;
	int						endian;
}							t_image;

typedef struct				s_cam
{
	double					offsetx;
	double					offsety;
	double					x;
	double					y;
	double					scale;
}							t_cam;

typedef struct				s_mouse
{
	bool					clicked;
	bool					locked;
	double					x;
	double					y;
	double					lastx;
	double					lasty;
}							t_mouse;

typedef struct				s_mlx
{
	char					*type;
	int						iterations;
	int						palette;
	int						p_size;
	bool					c_lock;
	bool					m_lock;
	void					*mlx;
	void					*window;
	t_image					*image;
	t_cam					*cam;
	t_mouse					*mouse;
}							t_mlx;

struct						s_triangle
{
	t_vect_2 parent[3];
	t_vect_2 child[3];
};

typedef struct				s_serp_args
{
	int						nb;
	t_mlx					*mlx;
	t_triangle				*in;
}							t_serp_args;

typedef struct				s_fractal_args
{
	double					xsize;
	double					ysize;
	double					screenx;
	double					screeny;
	double					xoffset;
	double					yoffset;
	double					xend;
	double					yend;
	t_mlx					*mlx;
}							t_fractal_args;

int							init(char *title, t_mlx *mlx);
void						mlx_draw(t_mlx *mlx);
void						mlxdel(t_mlx *mlx);
t_image						*new_image(t_mlx *mlx);
t_image						*del_image(t_mlx *mlx, t_image *img);
void						clear_image(t_image *image);
void						start(t_mlx *mlx);
void						image_set_pixel(t_image *image, int x,
								int y, int color);
void						dda(t_mlx *mlx, t_vect_2 start,
								t_vect_2 end, int it);
void						sierpinski_init(t_mlx *mlx);
void						fractal_check_print(t_mlx *mlx, int x,
								int y, int it);
void						*mandelbrot(void *args);
void						*julia(void *args);
int							colors(int i, t_mlx *mlx);
void						sierpinski_r(t_mlx *mlx, t_triangle tri,
								int i, bool first);
t_triangle					new_triangles(t_triangle *tri, int nb);
void						new_tri_helper(t_triangle *t, t_triangle *tri,
								int nb);
void						*sierpinski_thread(void *args);
void						sierpinski_helper(t_triangle t[3], t_mlx *mlx,
								int i, bool first);
void						cam_reset(t_mlx *mlx);
void						cam_scale(t_mlx *mlx, int x, int y, int arg);

#endif
