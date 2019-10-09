/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:16 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/09 16:36:45 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H
# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../minilibx_macos/mlx.h"

# define WIN_WIDTH 1300
# define WIN_HIGHT 980

# define MAGNET_RADIUS 30
# define SELECT_RADIUS 60
# define SELECT_PADDING 30
# define POINT_SIZE 4

# define OBJECT_SIZE 6
# define PLAYER_SIZE 8

# define DEFAULT_OBJ_TYPE 0

# define WALL_COLOR 0xECF7FF
# define SELECT_COLOR 0xFFD200
# define MENU_COLOR 0xA0A0A0
# define SEL_SEC_COLOR 0xFF3300
# define APP_SEC_COLOR 0x00FFFF
# define POINT_COLOR 0xFFFFFF
# define PORTAL_COLOR 0xe35c36
# define APP_PORTAL_COLOR 0xBF8EEA
# define GRID_COLOR 0x464646
# define PLAYER_COLOR 0x00FF00
# define OBJECT_COLOR 0xFF703C

# define PI_CEIL 4
# define PI_4 3.1415f

# define INST_PANEL_X 0
# define INST_PANEL_Y WIN_HIGHT / 5
# define INST_PANEL_SIZE_X 50
# define INST_PANEL_SIZE_Y 257
# define INST_NUM 5
# define MENU_XLEN 150
# define MENU_YLEN 120
# define I_MENU_XLEN 300
# define I_MENU_YLEN 170
# define I_SEC_MENU_YLEN 338
# define CHECKBOX_SIZE 20
# define LINE_SIZE_X 120
# define LINE_SIZE_Y 30
# define ICON_SIZE 50

# define ST_FLOOR_HIGHT 0
# define ST_CEIL_HIGHT 35
# define ST_ILLUMINATION 1.0f
# define ST_TEXTURE -1
# define ST_FTEX -1
# define ST_CTEX -1

# define COMPRESSING 30
# define UNIT_SIZE 0.5f

# define SKY 11

# define SAVEPATH "../maps/default_map"

# define BUFF_SIZE 100
# define FD_STORAGE_NUM 12

# define STR_SMALL 20
# define STR_MED 100
# define STR_LARGE 300

typedef struct					s_coord
{
	int							x;
	int							y;
}								t_coord;

typedef struct					s_fcoord
{
	float						x;
	float						y;
}								t_fcoord;

typedef struct					s_st
{
	int							s;
	int							t;
}								t_st;

typedef struct					s_wall
{
	t_coord						p1;
	t_coord						p2;
	int							index;
	float						len;
	int							color;
	t_st						sectors[2];
	int							isportal;
	int							isdoor;
	void						*next;
}								t_wall;

typedef struct					s_visual
{
	int							x0;
	int							y0;
	int							x1;
	int							y1;
	float						dx;
	float						dy;
	int							x0_copy;
	int							y0_copy;
	int							mem_x;
	int							mem_y;
	int							color;
	int							err;
}								t_visual;

typedef struct					s_select
{
	t_wall						*wall;
	float						dist;
	int							closest_wall;
	float						min_dist;
	float						p;
	float						a;
	float						b;
}								t_select;

typedef struct					s_msg
{
	char						**text;
	t_coord						pos;
	int							color;
	int							id;
}								t_msg;

typedef struct					s_elems
{
	int							isportal;
}								t_elems;

typedef struct					s_obj
{
	int							id;
	int							type;
	t_fcoord					fcoord;
	float						angle;
	int							sec;
	int							color;
	int							isplayer;
	void						*next;
}								t_obj;

typedef struct					s_sec
{
	int							id;
	float						floor;
	int							ftex;
	float						ceiling;
	int							ctex;
	float						illum;
	int							isdoor;
	int							isfinish;
	void						*next;
}								t_sec;

typedef struct					s_recsec
{
	char						*txt;
	char						*tmp;
	char						*conn;
	char						*wtx;
	int							doprint_wtx;
	t_wall						*wtmp;
	int							i;
	t_fcoord					cw;
	int							curr;
	t_sec						*sec;
}								t_recsec;

typedef struct					s_core
{
	void						*mlx;
	void						*win;
	void						*image;
	void						*idata;
	int							endian;
	int							bpp;
	int							linesize;
	int							tr;
	t_wall						*wlist;
	t_obj						**olist;
	t_sec						**slist;
	t_visual					vs;
	t_select					sl;
	t_recsec					rs;
	t_elems						cmenu_elems;
	int							lmb;
	int							rmb;
	void						*icons_trash;
	void						*hl_trash;
	void						*icons_data;
	void						*hl_data;
	void						*arrowl_trash;
	void						*arrowr_trash;
	void						*arrowl_data;
	void						*arrowr_data;
	int							menu_is_open;
	int							i_menu_is_open;
	t_wall						*i_menu_wall;
	int							wside;
	t_coord						click;
	int							idcurr;
	float						angle_mem;
	int							wpoint;
	int							wpoint_tmp;

	t_coord						inst_panel;
	t_coord						inst_panel_size;
	void						(*inst_func)(void *cr, int x, int y);
	int							highlight;

	t_list						**messages;

	int							sec_num;
	int							shift_button;
	int							ctrl_button;
	int							multi_sel;
	t_coord						idsec;
	t_coord						s[2];
	int							mpsw;

	t_coord						offs;
	t_coord						msmem;
	int							zoom;
	int							dragm;
	int							test;

	t_obj						player;
	t_coord						dir;
	t_coord						hit;
	float						dist;
	int							secmem[2];
	t_coord						debug;
	int							detect_cl;
	t_obj						*closest_obj;
	int							find_sec_color;
	int							sel_sec_id;
	int							searchtype;
	int							do_use_inst;
	int							vt[2];
	char						*tms;
	t_coord						p3;
	t_coord						rpoint;
	t_coord						rstart;
	int							show_obj_num;

	char						*gnlstr[FD_STORAGE_NUM];

}								t_core;

void							init(t_core		*cr);
void							err_ex(int pr);
void							redraw(t_core *cr);
void							img_new(t_core *cr);
void							img_pxl(void *td, int x, int y, int color);
void							pxl_put_wrap(void *td, int x, int y, int color);
int								red_button(t_core *pr);
int								key_action(int keycode, t_core *cr);
int								key_release(int keycode, t_core *cr);
int								mouse_press(int button, int x, int y, \
t_core *cr);
int								mouse_release(int button, int x, int y, \
t_core *cr);
int								mouse_move(int x, int y, t_core *cr);
void							bresenham(t_core *cr, \
void (*print_func)(void *, int, int, int));
void							add_wall(t_core *cr);
void							magnet(t_core *cr, int *x, int *y, \
int check_start);
float							calc_dist(int x0, int y0, int x1, int y1);
int								select_wall(t_core *cr, int x, int y);
t_wall							*find_by_index(t_core *cr, int index);
int								is_near_wall(t_core *cr, t_wall *wall, int x, \
int y);
int								min(int a, int b);
int								max(int a, int b);
void							draw_rectangle(t_core *cr, t_coord xy, \
t_coord ab, int color);
void							draw_rectangle_img_pxl(t_core *cr, t_coord xy, \
t_coord ab, int color);
void							rmb_menu(t_core *cr, t_wall *wall, \
int x, int y);
void							load_gui(t_core *cr);
void							display_instruments(t_core *cr);
void							halfplane(t_core *cr, t_wall *ref);
void							reset_color(t_core *cr);
int								choose_instrument(t_core *cr, int x, int y);
void							draw_wall(void *td, int x, int y);
void							eraser(void *td, int x, int y);
void							img_fill(void *idata, int color);
void							show_messages(t_core *cr);
void							add_message(t_core *cr, char **text, int pos, \
int color, int id);
int								find_msg_by_id(t_core *cr, int id);
void							highlight(t_core *cr);
void							iter_wall(t_core *cr, int pr1, int pr2, \
void (*f)(t_core *, t_wall *, int, int));
void							apply_sector(t_core *cr, t_wall *wall, \
int color1, int color2);
void							turn_color(t_core *cr, t_wall *wall, \
int color1, int color2);
void							redraw_color(t_core *cr, t_wall *wall, \
int exception1, int exception2);
void							straight_line(t_core *cr, int *x, int *y);
void							draw_nodes(t_core *cr, t_wall *wall, \
int pr1, int pr2);
void							find_multi_sel(t_core *cr);
void							check_menu_events(t_core *cr, int x, int y);
void							switch_isportal(t_core *cr, t_wall *wall, \
int switchval, int pr2);
void							remove_sectors(t_core *cr, t_wall *wall);
void							restore_sec_id(t_core *cr);
void							save_map(t_core *cr);
void							load_map(t_core *cr);
void							erase_by_id(t_core	*cr, int id);
int								find_rep_symb(char *line, char symb, int num);
t_wall							*get_last_wall(t_core *cr);
int								find_vt_id(t_core *cr, float x, float y);
void							count_sectors(t_core *cr, t_wall *wall, \
int pr1, int pr2);
int								check_bounds(int x, int y);
void							grid(t_core *cr);
void							grid_magnet(t_core *cr, int *x, int *y, \
int check_start);
double							ft_atof(const char *str);
char							*ft_ftoa(float num);

void							draw_player(t_core *cr);
void							record_player(t_core *cr, int fd);
void							spot_sector_around(t_core *cr, t_obj *obj);

void							new_sector(t_core *cr);
void							is_there_color(t_core *cr, t_wall *wall, \
int color, int pr2);
void							restore_sec_id_v2(t_core *cr);
void							load_player(t_core *cr);
void							draw_objects(t_core *cr);
void							draw_objects_text(t_core *cr);
void							add_object(t_core *cr, int x, int y);
void							del_object(t_core *cr, int idref);
void							info_menu(t_core *cr, t_wall *wall);
void							record_objects(t_core *cr, int fd);
void							obj_info_menu(t_core *cr, t_obj *obj);
float							sel_object(t_core *cr, int x, int y);
void							check_obj_events(int x, int y, t_obj *obj);
void							load_objects(t_core *cr);

void							sec_list_id_replace(t_core *cr, int new, \
int old);
void							del_sec_list(t_core *cr, int idref);
void							add_sec_list(t_core *cr);
void							name_sec_list(t_core *cr);
t_sec							*find_sec_list(t_core *cr, int idref);
void							print_sec_num(t_core *cr);
void							load_sec_info(t_core *cr);
void							check_obj_events_mwheel(t_coord click, \
int button, t_obj *obj);
void							check_wall_events_mwheel(t_coord click, \
int button, t_wall *wall);
void							check_wall_events(int x, int y, t_wall *wall);
void							find_sector(void *td, int x, int y);
void							select_sector(void *td, int x, int y);
void							sec_info_menu(t_core *cr, int secid);
void							checkbox_fill(t_core *cr, t_coord xy, \
t_coord ab);
void							check_sec_events_mwheel(t_core *cr, \
t_coord click, int button, int secid);
void							check_sec_events(t_core *cr, int x, int y, \
int secid);

void							valid_illum_val(float *val);
int								ft_arrlen(char	**arr);
void							err_ex(int pr);
void							del_last_sector(t_core *cr);
void							select_wall_wrap(void *td, int x, int y);
void							open_gamesave(int *fd);

void							process_walls(t_core *cr, char **pts, \
char **prt, int secnum);
void							load_doors(t_core *cr);
void							load_finish(t_core *cr);
int								check_dups(t_core *cr, t_coord inp1, \
t_coord inp2);
void							set_sectors(t_core *cr, t_coord inp1, \
t_coord inp2, int secnum);
void							restore_obj_color(t_core *cr);
int								check_vt_dups(t_core *cr, float	x, float y);
void							record_sectors(t_core *cr, int fd);
void							choose_direction(t_core *cr, t_fcoord *cw, \
t_wall *start, int secid);
int								find_next_wall(t_core *cr, t_fcoord *cw, \
int prev, int secid);
void							find_wall_by_xy(t_core *cr, t_coord inp1, \
t_coord inp2);
void							set_textures(t_core *cr, t_wall *wall, \
int texture, int secid);
int								find_w_id(t_core *cr);
void							get_last_sec(t_core *cr, t_wall *wall, \
int idref, int pr2);
int								does_sec_id_exist(t_core *cr, int idref);
void							sec_id_replace(t_core *cr, t_wall *wall, \
int idold, int idnew);
int								gnl_struct(char **gnlstr, const int fd, \
char **line);
void							prepare_gnlstr(char **str);
void							record_sectors_part3(t_core *cr);
void							record_sectors_partx(t_core *cr);
void							find_any_wall_in_sec(t_core *cr, t_wall *wall, \
int refid, int pr2);
void							strnew_nullcheck(char **str, int len);
void							end_reading(char **line, int fd);
int								validate_map(t_core *cr);

#endif
