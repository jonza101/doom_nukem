/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:24:36 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/03 18:21:34 by zjeyne-l         ###   ########.fr       */
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

typedef struct	s_vec2
{
	float			x;
	float			y;
}						t_vec2;

typedef struct	s_vec3
{
	float			x;
	float			y;
	float			z;
}						t_vec3;

typedef struct	s_item
{
	int					sector_n;
	int					sx1;
	int					sx2;
}						t_item;

typedef	struct	s_img
{
	void			*img;
	int					w;
	int					h;
	int					*data;
	int					bpp;
	int					size_line;
	int					endian;
}						t_img;

typedef struct	s_sector
{
	float			ceiling;
	float			floor;

	t_vec2			**verts;

	char				**texts;
	t_img				**textures;

	char			**neighbors;
	int					neighbors_count;
	int					verts_count;
}						t_sector;

typedef struct	s_scaler
{
	int					result;
	int					bop;
	int					fd;
	int					ca;
	int					cache;
}						t_scaler;

typedef	struct	s_player
{
	t_vec3			*pos;
	t_vec3			*velocity;

	float			eye_h;

	float			angle;
	float			sin_angle;
	float			cos_angle;
	float			yaw;
	
	int				sector;

	int				left;
	int				right;
	int				up;
	int				down;
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
	
	float				yaw;
	int					mouse_pos_x;
	int					mouse_pos_y;

	int					wsad[4];
	int					moving;
	int					falling;
	int					ground;
	int					crouching;

	t_item				queue[MAX_QUEUE];
	t_item				*head;
	t_item				*tail;
	t_item				*now;

	t_img				*texture;

	t_scaler			*scaler;
	t_scaler			*ya_int;
	t_scaler			*yb_int;
	t_scaler			*nya_int;
	t_scaler			*nyb_int;

	int					l;
	int					r;

	t_img				*txt_temp[TXT];
}						t_mlx;

void				ft_image(t_mlx *mlx, int x, int y, int color);

void				ft_load_map(t_mlx *mlx, char *map_file);

float				ft_min(float a, float b);
float				ft_max(float a, float b);
float				ft_clamp(float a, float min, float max);
int					ft_overlap(float a0, float a1, float b0, float b1);
int					ft_intersect_box(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);
float				ft_vec_cross_prod(float x0, float y0, float x1, float y1);
int					ft_point_side(float px, float py, float x0, float y0, float x1, float y1);
void				ft_intersect(t_vec2 *p, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
float				ft_yaw(float y, float z, float p_yaw);
t_scaler		*ft_scaler_init(t_scaler *scaler, int a, int b, int c, int d, int f);
int					ft_scaler_next(t_scaler *scaler);

void				ft_draw_vline(t_mlx *mlx, int x, int y1,int y2, int top_color,int middle_color,int bottom_color);
void				ft_draw_tvline(t_mlx *mlx, int x, int y1, int y2, t_scaler *ty, unsigned txtx, t_img *texture);

void				ft_draw(t_mlx *mlx);

void				ft_move_player(t_mlx *mlx, float dx, float dy);
void				ft_move_calc(t_mlx *mlx);
void				ft_collision(t_mlx *mlx);

void				ft_init_textures(t_mlx *mlx);

#endif
