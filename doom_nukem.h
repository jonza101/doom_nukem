/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:24:36 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/04 17:44:58 by zjeyne-l         ###   ########.fr       */
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
#include <pthread.h>

#define W 1280
#define H 720

#define EYE_H 6
#define CROUCH_H 3
#define HEAD_MARGIN 5
#define STAIRS_H 2
#define JUMP_H 0.75

#define FOV_H (0.63 * H)
#define FOV_V (0.2 * H)

#define MAX_QUEUE 32

#define THREAD 16

#define TXT 2

typedef struct		s_vec2
{
	double			x;
	double			y;
}					t_vec2;

typedef struct		s_vec3
{
	double			x;
	double			y;
	double			z;
}					t_vec3;

typedef struct		s_item
{
	int				sector_n;
	int				sx1;
	int				sx2;
}					t_item;

typedef	struct		s_img
{
	void			*img;
	int				w;
	int				h;
	int				*data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_img;

typedef struct		s_sector
{
	double			ceiling;
	double			floor;

	t_vec2			**verts;

	char			**texts;
	int				txt_count;

	char			**neighbors;
	int				neighbors_count;
	int				verts_count;
}					t_sector;

typedef struct		s_scaler
{
	int				result;
	int				bop;
	int				fd;
	int				ca;
	int				cache;
}					t_scaler;

typedef	struct		s_player
{
	t_vec3			*pos;
	t_vec3			*velocity;

	double			eye_h;

	double			angle;
	double			sin_angle;
	double			cos_angle;
	double			yaw;

	int				sector;

	int				left;
	int				right;
	int				up;
	int				down;
}					t_player;

typedef	struct		s_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	int				*data;
	int				bpp;
	int				size_line;
	int				endian;

	t_sector		**sect;
	int				num_sec;

	t_player		*player;
	
	double			yaw;
	int				mouse_pos_x;
	int				mouse_pos_y;

	int				wsad[4];
	int				moving;
	int				falling;
	int				ground;
	int				crouching;

	t_item			queue[MAX_QUEUE];
	t_item			*head;
	t_item			*tail;
	t_item			*now;

	t_img			*texture;

	t_scaler		*scaler;
	t_scaler		*ya_int;
	t_scaler		*yb_int;
	t_scaler		*nya_int;
	t_scaler		*nyb_int;

	int				l;
	int				r;

	t_img			*txt_temp[TXT];
}					t_mlx;

void				ft_image(t_mlx *mlx, int x, int y, int color);

void				ft_load_map(t_mlx *mlx, char *map_file);

double				ft_min(double a, double b);
double				ft_max(double a, double b);
double				ft_clamp(double a, double min, double max);
int					ft_overlap(double a0, double a1, double b0, double b1);
int					ft_intersect_box(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3);
double				ft_vec_cross_prod(double x0, double y0, double x1, double y1);
int					ft_point_side(double px, double py, double x0, double y0, double x1, double y1);
void				ft_intersect(t_vec2 *p, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
double				ft_yaw(double y, double z, double p_yaw);
t_scaler			*ft_scaler_init(t_scaler *scaler, int a, int b, int c, int d, int f);
int					ft_scaler_next(t_scaler *scaler);

void				ft_draw_vline(t_mlx *mlx, int x, int y1,int y2, int top_color,int middle_color,int bottom_color);
void				ft_draw_tvline(t_mlx *mlx, int x, int y1, int y2, t_scaler *ty, unsigned txtx, t_img *texture);

void				ft_draw(t_mlx *mlx);

void				ft_move_player(t_mlx *mlx, double dx, double dy);
void				ft_move_calc(t_mlx *mlx);
void				ft_collision(t_mlx *mlx);

void				ft_init_textures(t_mlx *mlx);

double				ft_datoi(char *str);

void				ft_upper_solid(t_mlx *mlx, int x, int cya, int cnya, int top_c, int middle_c, int bottom_c, int *ar_top);
void				ft_lower_solid(t_mlx *mlx, int x, int cnyb, int cyb, int bottom_c, int middle_c, int top_c, int *ar_bottom);
void				ft_upper_txt(t_mlx *mlx, int x, int cya, int cnya, int txtx, int txt_i, int ya, int yb, int *ar_top);
void				ft_lower_txt(t_mlx *mlx, int x, int cnyb, int cyb, int txtx, int txt_i, int ya, int yb, int *ar_bottom);

#endif
