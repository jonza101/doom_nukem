/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:24:10 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/16 18:27:58 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int ft_close(int i)
{
	i = 1;
	exit(0);
}

int ft_mouse_move(int x, int y, t_mlx *mlx)
{
	if (mlx->menu)
		return (0);
	if (x > mlx->mouse_pos_x || (mlx->mouse_pos_x == RIGHT && x == RIGHT))
		ftLookRight(mlx);
	else if (x < mlx->mouse_pos_x || (mlx->mouse_pos_x == LEFT && x == LEFT))
		ftLookLeft(mlx);
	if (y > mlx->mouse_pos_y || (mlx->mouse_pos_y == TOP && y == TOP))
		ftLookUp(mlx);
	else if (y < mlx->mouse_pos_y || (mlx->mouse_pos_y == BOTTOM && y == BOTTOM))
		ftLookDown(mlx);
	mlx->mouse_pos_x = x;
	mlx->mouse_pos_y = y;
	ft_move_player(mlx, 0, 0);
	return (0);
}

void ft_init_graphics(t_mlx *mlx)
{
	ft_init_textures(mlx);
	ft_init_obj(mlx);
	ft_init_wobj(mlx);
	ft_init_transparent(mlx);
	ft_init_sky(mlx);
	ft_init_font(mlx);
	ft_init_boost(mlx);
	ft_init_revolver(mlx);
	ft_init_shotgun(mlx);
	ft_init_arifle(mlx);

	ft_init_menu_font(mlx);
	ft_init_menu_buttons(mlx);
	ft_init_end(mlx);
}

void ft_init(t_mlx *mlx)
{
	mlx->player->cos_angle = cosf(mlx->player->angle);
	mlx->player->sin_angle = sinf(mlx->player->angle);
	mlx->player->velocity->x = 0;
	mlx->player->velocity->y = 0;
	mlx->player->velocity->z = 0;
	mlx->player->yaw = 0.0f;
	mlx->yaw = 0.0;
	mlx->ground = 0;
	mlx->falling = 1;
	mlx->moving = 0;
	mlx->crouching = 0;
	mlx->player->left = 0;
	mlx->player->right = 0;
	mlx->player->up = 0;
	mlx->player->down = 0;
	mlx->player->jump = 0;
	mlx->player->shift = 0;
	mlx->player->jetpack = 0;
	mlx->player->j_up = 0;
	mlx->player->j_down = 0;

	mlx->player->speed = 0.2f;

	mlx->player->speed_boost = 0;
	mlx->player->hp_boost = 0;

	mlx->player->hp = 100;
	mlx->player->max_hp = 100;
	int i = -1;
	while (++i < 4)
		mlx->player->wsad[i] = 0;

	mlx->player->weapon = mlx->player->revolver;
	mlx->player->frame = mlx->player->weapon->idle[0];
	mlx->player->weapon_state = 0;
	mlx->gun_fire_i = 0;
	mlx->gun_delay = 0;
	mlx->altfire = 0;
	mlx->fire_range = FIRE_RANGE;

	(!(mlx->scaler = (t_scaler*)malloc(sizeof(t_scaler)))) ? ft_mem_error() : 1;
	(!(mlx->ya_int = (t_scaler*)malloc(sizeof(t_scaler)))) ? ft_mem_error() : 1;
	(!(mlx->yb_int = (t_scaler*)malloc(sizeof(t_scaler)))) ? ft_mem_error() : 1;
	(!(mlx->nya_int = (t_scaler*)malloc(sizeof(t_scaler)))) ? ft_mem_error() : 1;
	(!(mlx->nyb_int = (t_scaler*)malloc(sizeof(t_scaler)))) ? ft_mem_error() : 1;

	(!(mlx->wya_int = (t_scaler*)malloc(sizeof(t_scaler)))) ? ft_mem_error() : 1;
	(!(mlx->wyb_int = (t_scaler*)malloc(sizeof(t_scaler)))) ? ft_mem_error() : 1;

	(!(mlx->rend_wobj = (t_rend_wobj**)malloc(sizeof(t_rend_wobj*) * MAX_WSPRITES_ON_WALL))) ? ft_mem_error() : 1;
	int w = -1;
	while (++w < MAX_WSPRITES_ON_WALL)
	{
		(!(mlx->rend_wobj[w] = (t_rend_wobj*)malloc(sizeof(t_rend_wobj)))) ? ft_mem_error() : 1;
		(!(mlx->rend_wobj[w]->wya_int = (t_scaler*)malloc(sizeof(t_scaler)))) ? ft_mem_error() : 1;
		(!(mlx->rend_wobj[w]->wyb_int = (t_scaler*)malloc(sizeof(t_scaler)))) ? ft_mem_error() : 1;
	}

	mlx->u0 = 0;
	mlx->u1 = 1024;
	mlx->c0 = 128;
	mlx->c1 = 128;

	mlx->s = 0;

	mlx->hud_r = 0;
	mlx->r_i = 0;
	mlx->r_i_d = 0;

	mlx->seg = 0;
	mlx->seg_i = 0;
	(!(mlx->opening = (int**)malloc(sizeof(int*) * H))) ? ft_mem_error() : 1;
	int y = -1;
	while (++y < H)
	{
		(!(mlx->opening[y] = (int*)malloc(sizeof(int) * W))) ? ft_mem_error() : 1;
		int x = -1;
		while (++x < W)
			mlx->opening[y][x] = -1;
	}

	mlx->sky_offset_x = 0;
	mlx->sky_offset_y = 100;

	(!(mlx->i1 = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;
	(!(mlx->i2 = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;
	(!(mlx->org1 = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;
	(!(mlx->org2 = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;

	(!(mlx->wi1 = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;
	(!(mlx->wi2 = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;
	(!(mlx->worg1 = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;
	(!(mlx->worg2 = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;

	(!(mlx->pos = (t_vec3*)malloc(sizeof(t_vec3)))) ? ft_mem_error() : 1;

	mlx->menu = 1;
	ft_init_menu_fire(mlx);
	y = -1;
	while (++y < H * 2)
	{
		int x = -1;
		while (++x < W)
		{
			if (y == H - 1)
				mlx->fire_buff[y * W + x] = 35;
			else
				mlx->fire_buff[y * W + x] = 0;
		}
	}
	mlx->button_i = 0;
	mlx->end = 0;
}

int main(int argc, char **argv)
{
	t_mlx *mlx;

	(!(mlx = (t_mlx *)malloc(sizeof(t_mlx)))) ? ft_mem_error() : 1;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "Doom-Nukem");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);

	mlx->player = (t_player *)malloc(sizeof(t_player));

	ft_init_graphics(mlx);
	if (argc == 2)
		ft_load_map(mlx, argv[1]);
	else
		ft_load_map(mlx, "maps/map4");
	ft_init(mlx);

	// mlx_hook(mlx->win, 6, 1L << 6, ft_mouse_move, mlx);
	mlx_hook(mlx->win, 4, 0, ft_mouse_press, mlx);
	mlx_hook(mlx->win, 5, 0, ft_mouse_release, mlx);
	mlx_loop_hook(mlx->mlx, ft_game_loop, mlx);
	mlx_hook(mlx->win, 2, 1L << 0, ft_key_press, mlx);
	mlx_hook(mlx->win, 3, 0, ft_key_realese, mlx);
	mlx_hook(mlx->win, 17, 0, ft_close, (void *)1);
	mlx_loop(mlx->mlx);
	return (0);
}
