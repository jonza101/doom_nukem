/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:24:36 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/15 20:44:17 by zjeyne-l         ###   ########.fr       */
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
#define HEAD_MARGIN 1
#define STAIRS_H 2
#define JUMP_H 0.75

#define FOV_H (1.0 * 0.63 * H / W)
#define FOV_V (1.0 * 0.2f)

#define MAX_QUEUE 32

#define UPPER_COLOR 0x330315
#define LOWER_COLOR 0x1B0030
#define WALL_COLOR 0x454545
#define CEILING_COLOR 0x252525
#define FLOOR_COLOR 0x252525
#define LINE_COLOR 0x0

#define IGNORE_COLOR 0xFF000000

#define MAX_DBL 1.7976931348623157E+308

#define THREAD 16

#define TXT 3
#define OBJ 1
#define TRANSPARENT 1
#define SKY 1

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

typedef struct		s_obj
{
	t_vec2			*pos;
	t_img			*img;
}					t_obj;

typedef struct		s_sector
{
	double			ceiling;
	double			floor;

	t_vec2			**verts;

	int				ceil_txt;
	int				floor_txt;
	char			**texts;
	int				txt_count;

	char			**neighbors;
	int				neighbors_count;

	char			**transparent;

	t_vec2			**objects;

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

	int				wsad[4];
	int				left;
	int				right;
	int				up;
	int				down;
	int				jump;
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

	int				moving;
	int				falling;
	int				ground;
	int				crouching;

	t_item			queue[MAX_QUEUE];
	t_item			*head;
	t_item			*tail;
	t_item			*now;

	t_scaler		*scaler;
	t_scaler		*ya_int;
	t_scaler		*yb_int;
	t_scaler		*nya_int;
	t_scaler		*nyb_int;

	double			map_x;
	double			map_z;

	int				l;
	int				r;

	t_img			*txt[TXT];
	t_img			*obj[OBJ];
	t_img			*transparent[TRANSPARENT];
	t_img			*sky[SKY];

	int				u0;
	int				u1;
	int				c0;
	int				c1;
}					t_mlx;

void				ft_image(t_mlx *mlx, int x, int y, int color);

void				ft_load_map(t_mlx *mlx, char *map_file);

double				ft_min(double a, double b);
double				ft_max(double a, double b);
double				ft_clamp(double a, double min, double max);
int					ft_overlap(int a0, int a1, int b0, int b1);
int					ft_intersect_box(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3);
double				ft_vec_cross_prod(double x0, double y0, double x1, double y1);
int					ft_point_side(double px, double py, double x0, double y0, double x1, double y1);
void				ft_intersect(t_vec2 *p, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4);
double				ft_yaw(double y, double z, double p_yaw);
void				ft_scaler_init(t_scaler *scaler, int a, int b, int c, int d, int f);
int					ft_scaler_next(t_scaler *scaler);

void				ft_draw_vline(t_mlx *mlx, int x, int y1,int y2, int top_color,int middle_color,int bottom_color);
void				ft_draw_tvline(t_mlx *mlx, int x, int y1, int y2, unsigned txtx, t_img *texture, int is_glass);

void				ft_draw(t_mlx *mlx);
void				ft_transparent(t_mlx *mlx);

void				ft_obj(t_mlx *mlx);

void				ft_move_player(t_mlx *mlx, double dx, double dy);
void				ft_move_calc(t_mlx *mlx);
void				ft_collision(t_mlx *mlx);

void				ft_init_textures(t_mlx *mlx);
void				ft_init_obj(t_mlx *mlx);
void				ft_init_transparent(t_mlx *mlx);
void				ft_init_sky(t_mlx *mlx);

double				ft_datoi(char *str);
void				ft_strsplit_free(char **temp);

void				ft_upper_solid(t_mlx *mlx, int x, int cya, int cnya, int top_c, int middle_c, int bottom_c, short *ar_top);
void				ft_lower_solid(t_mlx *mlx, int x, int cnyb, int cyb, int bottom_c, int middle_c, int top_c, short *ar_bottom);
void				ft_upper_txt(t_mlx *mlx, int x, int cya, int cnya, int txtx, int txt_i, int ya, int yb, short *ar_top);
void				ft_lower_txt(t_mlx *mlx, int x, int cnyb, int cyb, int txtx, int txt_i, int ya, int yb, short *ar_bottom);

void				ft_screenpoint_to_mappoint(t_mlx *mlx, double map_y, double screen_x, double screen_y);
void				ft_relative_to_absolute(t_mlx *mlx);

int					ft_line_intersect(t_vec2 *p0, t_vec2 *p1, t_vec2 *v0, t_vec2 *v1);
int					ft_is_inside(t_sector *sector, double px, double py, double dx, double dy);

void	ft_dr(t_mlx *mlx);

#endif
