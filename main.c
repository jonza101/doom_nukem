/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:24:10 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/24 14:55:53 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_image(t_mlx *mlx, int x, int y, int color)
{
	// nahooy this check
	//if (x >= 0 && x < W && y >= 0 && y < H)
	//TODO вынести это нахуй из функции? Можно получить прирост в производительности
	mlx->data[y * W + x] = mlx_get_color_value(mlx->mlx, color);
}

void	ft_reset_image(t_mlx *mlx)
{
	// with this bzero thing it works 2 times faster
	// you can check it with fps counter below
	ft_bzero(mlx->data, W * H * 4);
	// mlx_destroy_image(mlx->mlx, mlx->img);
	// mlx->img = mlx_new_image(mlx->mlx, W, H);
	// mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);
	// mlx_clear_window(mlx->mlx, mlx->win);
}

int		ft_close(int i)
{
	i = 1;
	exit(0);
}

// int		ft_mouse_move(int x, int y, t_mlx *mlx)
// {
// 	printf("x %d	y %d\n", x, y);
// 		if (x > mlx->mouse_pos_x)
// 			mlx->player->angle += x * 0.0001f;
// 		if (x < mlx->mouse_pos_x)
// 			mlx->player->angle -= x * 0.0001f;
// 		printf("yaww %f\n", mlx->yaw + y * 0.05f);
// 		mlx->yaw = ft_clamp(mlx->yaw - y * 0.05f, -0.5, 0.5);
// 		mlx->player->yaw = mlx->yaw - mlx->player->velocity->z * 0.5;
// 		printf("pyaw %f\n\n", mlx->player->yaw);
// 		mlx->mouse_pos_x = x;
// 		mlx->mouse_pos_y = y;
// 		ft_move_player(mlx, 0, 0);
// 	return (0);
// }

void	ft_init_graphics(t_mlx *mlx)
{
	ft_init_textures(mlx);
	ft_init_obj(mlx);
	ft_init_wobj(mlx);
	ft_init_transparent(mlx);
	ft_init_sky(mlx);

	ft_init_revolver(mlx);
	ft_init_shotgun(mlx);
	ft_init_arifle(mlx);
}

void	ft_init(t_mlx *mlx)
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
	int i = -1;
	while (++i < 4)
		mlx->player->wsad[i] = 0;

	mlx->player->weapon = mlx->player->revolver;
	mlx->player->weapon_state = 0;
	mlx->gun_fire_i = 0;
	mlx->gun_delay = 0;
	mlx->altfire = 0;
	mlx->fire_range = FIRE_RANGE;

	mlx->scaler = (t_scaler*)malloc(sizeof(t_scaler));
	mlx->ya_int = (t_scaler*)malloc(sizeof(t_scaler));
	mlx->yb_int = (t_scaler*)malloc(sizeof(t_scaler));
	mlx->nya_int = (t_scaler*)malloc(sizeof(t_scaler));
	mlx->nyb_int = (t_scaler*)malloc(sizeof(t_scaler));

	mlx->wya_int = (t_scaler*)malloc(sizeof(t_scaler));
	mlx->wyb_int = (t_scaler*)malloc(sizeof(t_scaler));

	mlx->rend_wobj = (t_rend_wobj**)malloc(sizeof(t_rend_wobj*) * MAX_WSPRITES_ON_WALL);
	int w = -1;
	while (++w < MAX_WSPRITES_ON_WALL)
	{
		mlx->rend_wobj[w] = (t_rend_wobj*)malloc(sizeof(t_rend_wobj));
		mlx->rend_wobj[w]->wya_int = (t_scaler*)malloc(sizeof(t_scaler));
		mlx->rend_wobj[w]->wyb_int = (t_scaler*)malloc(sizeof(t_scaler));
	}

	mlx->u0 = 0;
	mlx->u1 = 512;
	mlx->c0 = 128;
	mlx->c1 = 128;

	mlx->s = 0;

	mlx->seg = 0;
	mlx->seg_i = 0;
	mlx->opening = (short**)malloc(sizeof(short*) * H);
	int y = -1;
	while (++y < H)
	{
		mlx->opening[y] = (short*)malloc(sizeof(short) * W);
		int x = -1;
		while (++x < W)
			mlx->opening[y][x] = -1;
	}
}

int		main()
{
	t_mlx	*mlx;

	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "Doom-Nukem");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);

	mlx->player = (t_player*)malloc(sizeof(t_player));

	mlx->shoot_p = (t_vec2*)malloc(sizeof(t_vec2));

	ft_init_graphics(mlx);
	ft_load_map(mlx, "maps/map4");
	ft_init(mlx);

	// mlx_hook(mlx->win, 6, 1L<<6, ft_mouse_move, mlx);
	mlx_loop_hook(mlx->mlx, ft_game_loop, mlx);
	mlx_hook(mlx->win, 2, 1L << 0, ft_key_press, mlx);
	mlx_hook(mlx->win, 3, 0, ft_key_realese, mlx);
	mlx_hook(mlx->win, 17, 0, ft_close, (void*)1);
	mlx_loop(mlx->mlx);
	return (0);
}
