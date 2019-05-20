/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:52:20 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/20 18:47:15 by zjeyne-l         ###   ########.fr       */
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
}						t_triangle;

typedef	struct	s_mesh
{
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

	t_mesh			*cube;
	t_martix		*mat_proj;
	t_triangle		*tri_proj;
	t_triangle		*tri_translated;
	
	t_triangle		*tri_rotated_z;
	t_triangle		*tri_rotated_zx;
	t_triangle		*tri_rotated_zxy;
}						t_mlx;

void				ft_image(t_mlx *mlx, int x, int y, int color);

void				ft_init_cube(t_mlx *mlx);

void				ft_draw(t_mlx *mlx);

#endif
