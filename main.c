/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:24:10 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/06/25 18:09:47 by zjeyne-l         ###   ########.fr       */
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

// int		mouse_move(int x, int y, t_mlx *mlx)
// {
	// printf("x %d	y %d\n", x, y);
		// if (x > mlx->mouse_pos_x)
		// 	mlx->player->angle += x * 0.00001f;
		// if (x < mlx->mouse_pos_x)
		// 	mlx->player->angle -= x * 0.00001f;
// 		printf("yaww %f\n", mlx->yaw + y * 0.05f);
// 		mlx->yaw = ft_clamp(mlx->yaw - y * 0.05f, -0.5, 0.5);
// 		mlx->player->yaw = mlx->yaw - mlx->player->velocity->z * 0.5;
// 		printf("pyaw %f\n\n", mlx->player->yaw);
// 		mlx->mouse_pos_x = x;
// 		mlx->mouse_pos_y = y;
// 		ft_move_player(mlx, 0, 0);
// 	return (0);
// }

int		ft_game_loop(t_mlx *mlx)
{
	// ft_collision(mlx);
	// mlx->ground = 0;
	// mlx->falling = 1;
	// mlx->moving = 0;
	// mlx->crouching = 0;
	ft_collision(mlx);
	ft_move_calc(mlx);
	int i = -1;
	while (++i < 4)
		mlx->wsad[i] = 0;
	ft_reset_image(mlx);
	ft_draw(mlx);
	// printf("px %f	py %f\n", mlx->player->pos->x, mlx->player->pos->y);
	// printf("dx %f	dy %f	dz %f\n\n", mlx->player->velocity->x, mlx->player->velocity->y, mlx->player->velocity->z);
	return (0);
}

int		ft_key_press(int keycode, t_mlx *mlx)
{
	// printf("%d\n", keycode);
	(keycode == 65307) ? exit(0) : 1;

	if (keycode == 65361)	//	LOOK LEFT
	{
		mlx->player->angle -= 0.09f;
		ft_move_player(mlx, 0, 0);
	}
	if (keycode == 65363)	//	LOOK RIGHT
	{
		mlx->player->angle += 0.09f;
		ft_move_player(mlx, 0, 0);
	}
	if (keycode == 65362)	//	LOOK UP
	{
		mlx->player->yaw -= 0.25f - mlx->player->velocity->z * 0.5;
		mlx->player->yaw = ft_clamp(mlx->player->yaw, -15, 15);
	}
	if (keycode == 65364)	//	LOOK DOWN
	{
		mlx->player->yaw += 0.25f - mlx->player->velocity->z * 0.5;
		mlx->player->yaw = ft_clamp(mlx->player->yaw, -15, 15);
	}
	if (keycode == 65507)
	{
		if (mlx->sect[mlx->player->sector]->ceiling > mlx->player->pos->z + EYE_H)
			mlx->crouching = !mlx->crouching;
	}
	if (keycode == 32 && mlx->ground && !mlx->crouching)
		mlx->player->velocity->z += 0.75f;

	if (keycode == 1731)
	{
		mlx->wsad[0] = 1;
		return (0);
	}
	if (keycode == 1753)
	{
		mlx->wsad[1] = 1;
		return (0);
	}
	if (keycode == 1734)
	{
		mlx->wsad[2] = 1;
		return (0);
	}
	if (keycode == 1751)
	{
		mlx->wsad[3] = 1;
		return (0);
	}
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

	mlx->texture = (t_image*)malloc(sizeof(t_image));
	mlx->texture->w = 512;
	mlx->texture->h = 512;
	mlx->texture->img = mlx_xpm_file_to_image(mlx->mlx, "textures/brick.xpm", &mlx->texture->w, &mlx->texture->h);
	mlx->texture->data = (int*)mlx_get_data_addr(mlx->texture->img, &mlx->texture->bpp, &mlx->texture->size_line, &mlx->texture->endian);

	mlx->scaler = (t_scaler*)malloc(sizeof(t_scaler));
	mlx->ya_int = (t_scaler*)malloc(sizeof(t_scaler));
	mlx->yb_int = (t_scaler*)malloc(sizeof(t_scaler));
	mlx->nya_int = (t_scaler*)malloc(sizeof(t_scaler));
	mlx->nyb_int = (t_scaler*)malloc(sizeof(t_scaler));
}

int		main()
{
	t_mlx	*mlx;

	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "Doom-Nukem");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);

	ft_load_map(mlx, "map");

	ft_init(mlx);

	mlx_hook(mlx->win, 2, 1L << 0, ft_key_press, mlx);
	// mlx_hook(mlx->win, 6, 1L<<6, mouse_move, mlx);
	mlx_loop_hook(mlx->mlx, ft_game_loop, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
