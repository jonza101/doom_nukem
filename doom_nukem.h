/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:52:20 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/06/03 23:20:45 by zjeyne-l         ###   ########.fr       */
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

#define EYE_H 6
#define CROUCH_H 3
#define HEAD_MARGIN 1
#define STAIRS_H 2

#define FOV_H (0.73 * H)
#define FOV_V (0.2 * H)

typedef struct	s_vec2
{
	double			x;
	double			y;
}						t_vec2;

typedef struct	s_vec3
{
	double			x;
	double			y;
	double			z;
}						t_vec3;

typedef struct	s_sector
{
	double			ceiling;
	double			floor;

	t_vec2			**verts;
	
	char			*neighbors;
	int					verts_count;
}						t_sector;

typedef	struct	s_player
{
	t_vec3			*pos;
	t_vec3			*velocity;

	double			eye_h;

	double			angle;
	double			sin_angle;
	double			cos_angle;
	double			yaw;
	
	int					sector;
}						t_player;

typedef	struct	s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	int					*data;
	int					bpp;
	int					size_line;
	int					endian;

	t_sector		**sect;
	int					num_sec;

	t_player		*player;

}						t_mlx;

void				ft_image(t_mlx *mlx, int x, int y, int color);

void				ft_load_map(t_mlx *mlx, char *map_file);

double				ft_min(double a, double b);
double				ft_max(double a, double b);
double				ft_clamp(double a, double min, double max);
int						ft_overlap(double a0, double a1, double b0, double b1);
int						ft_intersect_box(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3);
double				ft_vec_cross_prod(double x0, double y0, double x1, double y1);
double				ft_point_side(double px, double py, double x0, double y0, double x1, double y1);
t_vec2				*ft_intersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);

void				ft_draw_line(t_mlx *mlx, int xo, int yo, int x, int y, int color);

#endif
