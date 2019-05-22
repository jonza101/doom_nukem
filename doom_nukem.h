/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:52:20 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/22 19:32:38 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

#include "mlx.h"
#include "gnl/get_next_line.h"
#include "mac_keys.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define W 1280
#define H 720

typedef	struct	s_matrix
{
	double			mat[4][4];
}						t_martix;

typedef struct	s_vector_3d
{
	double			x;
	double			y;
	double			z;
}						t_vector_3d;

typedef	struct	s_triangle
{
	t_vector_3d		*points[3];
	int						color;
}						t_triangle;

typedef	struct	s_mesh
{
	int					tri_count;
	t_triangle		*triangles;
}						t_mesh;



typedef	struct	s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	int					*data;
	int					bpp;
	int					size_line;
	int					endian;

	double			theta;
	double			angle;

	t_vector_3d	*v_camera;

	t_mesh			*cube;
	t_mesh			*pyra;
	t_mesh			*octahedron;

	t_mesh			*ch_fig;

	t_martix		*mat_proj;
	t_triangle		*tri_proj;
	t_triangle		*tri_translated;
	
	t_triangle		*tri_rotated_z;
	t_triangle		*tri_rotated_zx;
	t_triangle		*tri_rotated_zxy;

	t_vector_3d	*normal;
	t_vector_3d	*line_1;
	t_vector_3d	*line_2;

	t_vector_3d *light_dir;
}						t_mlx;

void				ft_image(t_mlx *mlx, int x, int y, int color);

void				ft_init_cube(t_mlx *mlx);
void				ft_init_pyra(t_mlx *mlx);
void				ft_init_octahedron(t_mlx *mlx);

void				ft_draw(t_mlx *mlx, t_mesh *fig);

void				ft_draw_line(t_mlx *mlx, int xo, int yo, int x, int y, int color);
void				ft_draw_triangle(t_mlx *mlx, int x1, int y1, int x2, int y2, int x3, int y3, int color);
void				ft_fill_triangle(t_mlx *mlx, int x1, int y1, int x2, int y2, int x3, int y3, int color);

#endif
