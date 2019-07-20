/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:24:10 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/20 18:01:13 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_image(t_mlx *mlx, int x, int y, int color)
{
	if (x >= 0 && x < W && y >= 0 && y < H)
		mlx->data[y * W + x] = mlx_get_color_value(mlx->mlx, color);
}

void	ft_reset_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);
	mlx_clear_window(mlx->mlx, mlx->win);
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

void	ft_player_view(t_mlx *mlx)
{	
	if (mlx->player->left)
	{
		mlx->player->angle -= 0.045f;
		// mlx->player->sin_angle = sinf(mlx->player->angle);
		// mlx->player->cos_angle = cosf(mlx->player->angle);
		ft_move_player(mlx, 0, 0);
	}
	if (mlx->player->right)
	{
		mlx->player->angle += 0.045f;
		// mlx->player->sin_angle = sinf(mlx->player->angle);
		// mlx->player->cos_angle = cosf(mlx->player->angle);
		ft_move_player(mlx, 0, 0);
	}
	if (mlx->player->up)
	{
		mlx->player->yaw -= 0.15f;
		mlx->player->yaw = ft_clamp(mlx->player->yaw, -10, 10);
	}
	if (mlx->player->down)
	{
		mlx->player->yaw += 0.15f;
		mlx->player->yaw = ft_clamp(mlx->player->yaw, -10, 10);
	}
}

int		ft_key_realese(int keycode, t_mlx *mlx)
{
	if (keycode == MAC_LEFT)
		mlx->player->left = 0;
	if (keycode == MAC_RIGHT)
		mlx->player->right = 0;
	if (keycode == MAC_UP)
		mlx->player->up = 0;
	if (keycode == MAC_DOWN)
		mlx->player->down = 0;

	if (keycode == MAC_SPACE)
		mlx->player->jump = 0;

	if (keycode == MAC_W)
		mlx->player->wsad[0] = 0;
	if (keycode == MAC_S)
		mlx->player->wsad[1] = 0;
	if (keycode == MAC_A)
		mlx->player->wsad[2] = 0;
	if (keycode == MAC_D)
		mlx->player->wsad[3] = 0;
	return (0);
}

int		ft_key_press(int keycode, t_mlx *mlx)
{
	// printf("%d\n", keycode);
	(keycode == MAC_ESC) ? exit(0) : 1;
	if (keycode == MAC_LEFT)
		mlx->player->left = 1;
	if (keycode == MAC_RIGHT)
		mlx->player->right = 1;
	if (keycode == MAC_UP)
		mlx->player->up = 1;
	if (keycode == MAC_DOWN)
		mlx->player->down = 1;
	if (keycode == MAC_CTRL_L)
	{
		if (mlx->crouching)
		{
			if (mlx->sect[mlx->player->sector]->ceiling >= mlx->player->pos->z + (EYE_H - CROUCH_H))
			{
				mlx->crouching = 0;
				mlx->falling = 1;
			}
		}
		else
		{
			mlx->crouching = 1;
			mlx->falling = 1;
		}
		
	}
	if (keycode == MAC_SPACE && mlx->ground && !mlx->crouching)
		mlx->player->jump = 1;

	if (keycode == MAC_W)
		mlx->player->wsad[0] = 1;
	if (keycode == MAC_S)
		mlx->player->wsad[1] = 1;
	if (keycode == MAC_A)
		mlx->player->wsad[2] = 1;
	if (keycode == MAC_D)
		mlx->player->wsad[3] = 1;

	if (keycode == MAC_NUM_PLUS)
	{
		mlx->u1 += 32;
		mlx->c1 += 32;
		printf("u1 %d\n", mlx->u1);
	}
	if (keycode == MAC_NUM_MINUS && mlx->u1 > 128)
	{
		mlx->u1 -= 32;
		mlx->c1 -= 32;
		printf("u1 %d\n", mlx->u1);
	}
	if (keycode == MAC_EQUAL)
	{
		mlx->u0 += 32;
		mlx->c0 += 32;
		printf("u0 %d\n", mlx->u0);
	}
	if (keycode == MAC_MINUS)
	{
		mlx->u0 -= 32;
		mlx->c0 -= 32;
		printf("u0 %d\n", mlx->u0);
	}

	if (keycode == MAC_DOT)
		mlx->s = !mlx->s;
	return (0);
}

int		ft_game_loop(t_mlx *mlx)
{
	ft_collision(mlx);
	ft_player_view(mlx);
	ft_move_calc(mlx);
	if (mlx->player->jump && mlx->ground && !mlx->crouching)
	{
		mlx->player->velocity->z += JUMP_H;
		mlx->falling = 1;
	}
	ft_reset_image(mlx);
	ft_draw(mlx);
	ft_obj(mlx);
	// ft_transparent(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	// printf("s %d\n", mlx->s);
	// printf("p_sect %d\n", mlx->player->sector);
	// printf("px %f	py %f	pz %f\n", mlx->player->pos->x, mlx->player->pos->y, mlx->player->pos->z);
	// printf("angle %f	sin %f	cos %f\n", mlx->player->angle, mlx->player->sin_angle, mlx->player->cos_angle);
	// printf("dx %f	dy %f	dz %f\n\n", mlx->player->velocity->x, mlx->player->velocity->y, mlx->player->velocity->z);
	// printf("g %d\nf %d\nm %d\nc %d\n\n", mlx->ground, mlx->falling, mlx->moving, mlx->crouching);
	// printf("\n");
	return (0);
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

	mlx->scaler = (t_scaler*)malloc(sizeof(t_scaler));
	mlx->ya_int = (t_scaler*)malloc(sizeof(t_scaler));
	mlx->yb_int = (t_scaler*)malloc(sizeof(t_scaler));
	mlx->nya_int = (t_scaler*)malloc(sizeof(t_scaler));
	mlx->nyb_int = (t_scaler*)malloc(sizeof(t_scaler));

	mlx->u0 = 0;
	mlx->u1 = 512;
	mlx->c0 = 128;
	mlx->c1 = 128;

	mlx->s = 1;
}

int		main()
{
	t_mlx	*mlx;

	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "Doom-Nukem");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);

	ft_init_textures(mlx);
	ft_init_obj(mlx);
	ft_init_transparent(mlx);
	ft_init_sky(mlx);
	ft_load_map(mlx, "maps/map3");
	ft_init(mlx);

	t_obj *obj = mlx->obj_list;
	while (obj)
	{
		printf("sect %d			index %d\n", obj->specs->sect, obj->specs->txt_index);
		printf("x %f		y %f\n", obj->specs->x, obj->specs->y);
		if (obj->prev)
		{
			printf("prev_sect %d		prev_index %d\n", obj->prev->specs->sect, obj->prev->specs->txt_index);
			printf("prev_x %f		prev_y %f\n", obj->prev->specs->x, obj->prev->specs->y);
		}
		else
			printf("prev -\n");
		printf("\n------------------------------------------------\n");
		obj = obj->next;
	}

	// mlx_hook(mlx->win, 6, 1L<<6, ft_mouse_move, mlx);
	mlx_loop_hook(mlx->mlx, ft_game_loop, mlx);
	mlx_hook(mlx->win, 2, 1L << 0, ft_key_press, mlx);
	mlx_hook(mlx->win, 3, 0, ft_key_realese, mlx);
	mlx_hook(mlx->win, 17, 0, ft_close, (void*)1);
	mlx_loop(mlx->mlx);
	return (0);
}
