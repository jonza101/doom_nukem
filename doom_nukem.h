/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:24:36 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/06/09 22:53:35 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

#include "mlx.h"
#include "gnl/get_next_line.h"
// #include "mac_keys.h"

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

#define FOV_H (0.73 * H)
#define FOV_V (0.2 * H)

#define MAX_QUEUE 32

#define THREAD 16

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

typedef struct	s_sector
{
	float			ceiling;
	float			floor;

	t_vec2			**verts;
	
	char			**neighbors;
	int					neighbors_count;
	int					verts_count;
}						t_sector;

typedef	struct	s_player
{
	t_vec3			*pos;
	t_vec3			*velocity;

	float			eye_h;

	float			angle;
	float			sin_angle;
	float			cos_angle;
	float			yaw;
	
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

	int					thread_i;

	t_sector		**sect;
	int					num_sec;

	t_item			*item;
	t_item			*head;
	t_item			*tail;
	t_item			queue[MAX_QUEUE];
	t_item			*now;

	t_player		*player;

	t_vec2			**verts;

	t_vec2 *i1, *i2;

}						t_mlx;

void				ft_image(t_mlx *mlx, int x, int y, int color);

void				ft_load_map(t_mlx *mlx, char *map_file);

int						ft_min(int a, int b);
int						ft_max(int a, int b);
int						ft_clamp(int a, int min, int max);
int						ft_overlap(float a0, float a1, float b0, float b1);
int						ft_intersect_box(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3);
float					ft_vec_cross_prod(float x0, float y0, float x1, float y1);
float					ft_point_side(float px, float py, float x0, float y0, float x1, float y1);
void					ft_intersect(t_vec2 *p, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);

void				ft_draw(t_mlx *mlx);

void				ft_draw_vline(t_mlx *mlx, int x, int y1,int y2, int top_color,int middle_color,int bottom_color);

void				ft_thread(t_mlx *mlx);

void	ft_draw_screen(t_mlx *mlx);
void LoadData();

#endif
