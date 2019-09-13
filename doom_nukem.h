/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom_nukem.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:24:36 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/13 20:28:43 by adoyle           ###   ########.fr       */
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
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

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

#define MAX_DRAWSEG 256
#define MAX_VISSPRITES 64
#define MAX_VISWSPRITES 64
#define MAX_WSPRITES_ON_WALL 128
#define MAX_VISTRANSPARENT 64

// #define DBL_MAX 1.7976931348623158e+308

#define UPPER_COLOR 0x330315
#define LOWER_COLOR 0x1B0030
#define WALL_COLOR 0x454548
#define CEILING_COLOR 0x252525
#define FLOOR_COLOR 0x252525
#define LINE_COLOR 0x0

#define IGNORE_COLOR 0xFF000000
#define IGNORE_COLOR1 0x001000
#define IGNORE_COLOR2 0x0

#define REVOLVER_AMMO 6
#define SHOTGUN_AMMO 8
#define ARIFLE_AMMO 30

#define THREAD 16

#define TXT 4					//		3	-	DOOR
#define OBJ 20
#define WOBJ 9
#define TRANSPARENT 4
#define SKY 1
#define BOOST 2
#define FONT 13

#define FIRE_RANGE 10000
#define MELEE_RANGE 1
#define INTERACT_RANGE 2.5
#define SPEED_BOOST_DUR 30
#define	HP_BOOST_DUR 30
#define MAX_DOOR_DIST_VOL 50

#define DOOR_TIME 10

#define RIGHT 2459
#define LEFT -100
#define BOTTOM -621
#define TOP 818

#define VOLUME 128
#define COUNT_CH 22
#define SHOTS_CH 15
#define STEP_CH 20
#define RELOAD_CH 16
#define JUMP_CH 21
#define SWICH_CH 17
#define BOOM_CH 18

/*
Mix_channels

15 - shots
16 - reload
20 - step
21 - jump
17 - swich/door
 */

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

typedef struct		s_scaler
{
	int				result;
	int				bop;
	int				fd;
	int				ca;
	int				cache;
}					t_scaler;

typedef struct		s_obj_specs
{
	double			x;
	double			y;
	double			z;
	int				sect;

	double			pov;

	int				x1;
	int				x2;
	int				y1;
	int				y2;

	t_img			*frame;
	int				anim_i;
	int				del;

	int				obj_i;
	short			expl_f;

	short			has_collider;
	t_vec2			**verts;
}					t_obj_specs;

typedef	struct		s_wobj_specs
{
	short			is_switcher;

	double			abs_w;
	double			abs_h;
	double			aspect_ratio;

	int				u0;
	id_t			u1;
}					t_wobj_specs;

typedef struct		s_anim_list
{
	t_img			**anim;
	int				anim_n;
	int				delay;

	double			scaler;
	double			aspect_scaler;

	short			expl;
	short			is_collectable;
	double			col_w;

	int				can_rotate;
	t_img			**rot;

	short			can_shade;

	t_wobj_specs	*wobj_specs;
}					t_anim_list;

typedef	struct		s_trans
{
	int				sect;
	int				side;

	int				trans_i;

	struct s_trans	*next;
	struct s_trans	*prev;
}					t_trans;

typedef	struct		s_obj
{
	t_obj_specs		*specs;
	double			dist;
	int 			chan;

	struct s_obj	*next;
}					t_obj;

typedef	struct		s_wobj
{
	t_vec3			*pos;
	t_vec2			*p1;
	t_vec2			*p2;
	int				sect;
	int				side;
	int				wobj_i;

	short			rendered;

	t_img			*frame;
	int				anim_i;
	int				del;

	struct s_wobj	*next;
}					t_wobj;

typedef	struct		s_sect_wobj
{
	int				*side;
}					t_sect_wobj;

typedef struct		s_rend_wobj
{
	t_wobj			*wobj;

	short			w_flag;

	double			wvx1;
	double			wvy1;
	double			wvx2;
	double			wvy2;

	double			wtx1;
	double			wtz1;
	double			wtx2;
	double			wtz2;

	int				wu0;
	int				wu1;

	int				wy1a;
	int				wy1b;
	int				wy2a;
	int				wy2b;

	double			wxscale1;
	double			wyscale1;
	double			wxscale2;
	double			wyscale2;

	int				wx1;
	int				wx2;

	double			wyceil;
	double			wyfloor;

	int				wbeginx;
	int				wendx;

	t_scaler		*wya_int;
	t_scaler		*wyb_int;
}					t_rend_wobj;

typedef struct		s_drawseg
{
	short			seg_type;

	int				x1;
	int				x2;

	int				sect;

	double			dist;

	double			min_dist;
	double			max_dist;
}					t_drawseg;

typedef struct		s_sector
{
	double			ceiling;
	double			floor;

	t_vec2			**verts;
	int				verts_count;

	int				ceil_txt;
	int				floor_txt;
	char			**texts;
	int				txt_count;

	short			sky;

	short			is_door;
	double			start_ceiling;
	short			close;
	short			open;
	short			up;
	time_t			start_time;
	double			door_dist;

	int				*neighbors;
	int				neighbors_count;

	short			light;
	double			lum;
	short			has_switcher;

	t_obj			*obj_list;
	t_obj			*obj_head;
	int				obj_count;
}					t_sector;

typedef	struct		s_weapon
{
	t_img			**fire;
	t_img			**idle;
	t_img			**altfire;
	t_img			**altfire_cont;

	t_img			**reloading;
	short			reloading_n;
	short			reloading_delay;

	short			has_reload_ptt;
	t_img			**reloading_ptt;
	short			reloading_ptt_n;

	int				mag_ammo;
	int				ammo_count;
	int				mag_ammo_count;

	short			has_altfire;

	short			fire_n;
	short			altfire_n;
	short			altfire_cont_n;

	short			fire_delay;
	short			altfire_delay;
	short			altfire_cont_delay;

	double			scaler;
	int				x_offset;
	Mix_Chunk		*shot;
	Mix_Chunk		*reload;
	Mix_Chunk		*assreloadshort;
	Mix_Chunk		*assreload;
	Mix_Chunk		*assreloadboost;
	Mix_Chunk		*assreloadboostshort;
}					t_weapon;

typedef	struct		s_boost
{
	int				boost_i;

	t_img			*frame;
	int				del;
	int				anim_i;
}					t_boost;

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

	short			wsad[4];
	double			speed;
	short			left;
	short			right;
	short			up;
	short			down;
	short			jump;
	short			shift;
	short			j_up;
	short			j_down;

	int				hp;
	int				max_hp;

	short			speed_boost;
	time_t			speed_begin;
	time_t			speed_curr;
	double			speed_diff;

	short			hp_boost;
	time_t			hp_begin;
	time_t			hp_curr;
	double			hp_diff;

	short			jetpack;

	short			weapon_state;		//		IDLE - 0	|	FIRE - 1	|	ALTFIRE - 2		|	RELOADING - 3	|	RELOADING_PTT - 4	|

	t_img			*frame;
	t_weapon		*weapon;

	t_weapon		*revolver;
	t_weapon		*shotgun;
	t_weapon		*a_rifle;
}					t_player;

typedef struct s_music
{
	Mix_Music	*mus1;
	Mix_Music	*mus2;
	Mix_Music	*mus3;
	Mix_Music	*mus4;
	Mix_Music	*mus5;
	int			nummus;
}				t_music;

typedef struct s_bup
{
	Mix_Chunk	*fire;
	Mix_Chunk	*step;
	int			cstep;
	Mix_Chunk	*jump;
	Mix_Chunk	*swich;
	Mix_Chunk	*door;
	Mix_Chunk	*boom;
}				t_bup;

typedef struct	s_snd
{
	t_music		*music;
	t_bup		*chunks;
}				t_snd;

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

	short			moving;
	short			falling;
	short			ground;
	short			crouching;

	t_item			queue[MAX_QUEUE];
	t_item			*head;
	t_item			*tail;
	t_item			*now;

	t_scaler		*scaler;
	t_scaler		*ya_int;
	t_scaler		*yb_int;
	t_scaler		*nya_int;
	t_scaler		*nyb_int;

	t_scaler		*wya_int;
	t_scaler		*wyb_int;

	double			map_x;
	double			map_z;

	short			s;

	t_img			*txt[TXT];
	t_anim_list		**obj_l;
	t_anim_list		**wobj_l;
	t_anim_list		**trans;
	t_img			*sky[SKY];
	t_img			*font[FONT];

	int				hud_x;
	short			hud_r;
	short			r_i;
	short			r_i_d;

	t_boost			*boost[BOOST];

	int 			sky_offset_x;
	int				sky_offset_y;

	int				obj_i;

	t_trans			*trans_list;
	int				trans_count;
	int				trans_i;
	int 			r_trans;

	t_wobj			*wobj_list;
	t_wobj			*last_wobj;
	int				wobj_count;
	t_rend_wobj		**rend_wobj;
	t_sect_wobj		**sect_wobj;


	int				seg_i;
	t_drawseg		drawseg[MAX_DRAWSEG];
	int				seg;
	int				**opening;
	short			open_f;

	double			fire_range;
	t_vec2			*shoot_p;

	int				activated_doors;

	int				cya;
	int				cyb;
	int				cnya;
	int				cnyb;

	int				u0;
	int				u1;
	int				c0;
	int				c1;

	t_vec2			*i1;
	t_vec2			*i2;
	t_vec2			*org1;
	t_vec2			*org2;

	t_vec2			*p0;
	t_vec2			*p1;
	t_vec3			*pos;

	short 			gun_fire_i;
	short			gun_delay;
	short			altfire;
	short			del;

	t_snd			*snd;
}					t_mlx;

//adoyle
void				sound_eff(t_mlx *mlx);
void				ft_init_obj(t_mlx *mlx);


void				ft_image(t_mlx *mlx, int x, int y, int color);


void				ft_load_map(t_mlx *mlx, char *map_file);

double				ft_min(double a, double b);
double				ft_max(double a, double b);
double				ft_clamp(double a, double min, double max);
int					ft_overlap(double a0, double a1, double b0, double b1);
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

void				ft_move_player(t_mlx *mlx, double dx, double dy);
void				ft_move_calc(t_mlx *mlx);
void				ft_collision(t_mlx *mlx);
void				ft_player_view(t_mlx *mlx);

void				ft_init_textures(t_mlx *mlx);
void				ft_ini(t_mlx *mlx);
void				ft_init_wobj(t_mlx *mlx);
void				ft_init_transparent(t_mlx *mlx);
void				ft_init_sky(t_mlx *mlx);
void				ft_init_font(t_mlx *mlx);

void				ft_init_anim_obj(t_mlx *mlx);

void				ft_init_revolver(t_mlx *mlx);
void				ft_init_shotgun(t_mlx *mlx);
void				ft_init_arifle(t_mlx *mlx);

void				ft_draw_weapon(t_mlx *mlx);
void				ft_weapon_state(t_mlx *mlx);
void				ft_gun_anim(t_mlx *mlx, t_weapon *gun, int delay, int cont_delay);

double				ft_datoi(char *str);
void				ft_strsplit_free(char **temp);

void				ft_upper_solid(t_mlx *mlx, int x, int cya, int cnya, int top_c, int middle_c, int bottom_c, short *ar_top);
void				ft_lower_solid(t_mlx *mlx, int x, int cnyb, int cyb, int bottom_c, int middle_c, int top_c, short *ar_bottom);
void				ft_upper_txt(t_mlx *mlx, int x, int cya, int cnya, int txtx, int txt_i, int ya, int yb, short *ar_top);
void				ft_lower_txt(t_mlx *mlx, int x, int cnyb, int cyb, int txtx, int txt_i, int ya, int yb, short *ar_bottom);

void				ft_screenpoint_to_mappoint(t_mlx *mlx, double map_y, double screen_x, double screen_y);
void				ft_relative_to_absolute(t_mlx *mlx);

int					ft_texture_sampling(t_img *img, double sample_x, double sample_y);

int					ft_game_loop(t_mlx *mlx);
void				ft_game_mechanics(t_mlx *mlx);

int					ft_key_press(int keycode, t_mlx *mlx);
int					ft_key_realese(int keycode, t_mlx *mlx);

void				ft_opening_clear(t_mlx *mlx);
void				ft_drawseg_clear(t_mlx *mlx);

void				ft_sect_obj_sort(t_mlx *mlx, int sect);
void				ft_sect_obj(t_mlx *mlx, int sect);
void				ft_drawseg_sort(t_mlx *mlx);

void				ft_thread(t_mlx *mlx);

void				ft_drawseg_error();

void				ft_draw_sector_obj(t_mlx *mlx, t_obj *obj, int sector);
void				ft_find_obj_sect(t_mlx *mlx, int sector);

int					ft_find_trans_sect(t_mlx *mlx, int sector, int side);

void				ft_bzero(void *s, size_t n);

void				ft_obj_anim(t_mlx *mlx, t_obj *obj);
void				ft_wobj_anim(t_mlx *mlx, t_wobj *wobj);

int					ft_shoot_obj(t_mlx *mlx, double p_dist, int sect);

void				ft_shoot(t_mlx *mlx);

void				ft_wobj_pos_correct(t_mlx *mlx);
void				ft_wobj_specs_calc(t_mlx *mlx, t_sector *sector, int s, int w_count);
void				ft_add_wobj(t_mlx *mlx, t_vec3 *pos, int sect, int side);

int					ft_line_intersect(t_mlx *mlx, t_vec2 *p0, t_vec2 *p1, t_vec2 *v0, t_vec2 *v1);

int					ft_color_convert(int color, double lum);

void				ft_interact(t_mlx *mlx);
void				ft_interact_check(t_mlx *mlx, int sect, int side, t_vec3 *pos);

void				ft_obj_search(t_mlx *mlx);

void				ft_boost_check(t_mlx *mlx);
void				ft_init_boost(t_mlx *mlx);

void				ftLookRight(t_mlx *mlx);
void				ftLookLeft(t_mlx *mlx);
void				ftLookUp(t_mlx *mlx);
void				ftLookDown(t_mlx *mlx);

int					ft_mouse_press(int keycode, int x, int y, t_mlx *mlx);
int					ft_mouse_release(int keycode, int x, int y, t_mlx *mlx);

#endif
